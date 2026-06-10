/*
    Mavox-ID | https://ye-a.pp.ua
    Copyright (C) 2026  Mavox-ID

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <drm/drmP.h>
#include <drm/i915_drm.h>
#include "i915_drv.h"

/*
 * The BIOS typically reserves some of the system's memory for the exclusive
 * use of the integrated graphics. This memory is no longer available for
 * use by the OS and so the user finds that his system has less memory
 * available than he put in. We refer to this memory as stolen.
 *
 * The BIOS will allocate its framebuffer from the stolen memory. Our
 * goal is try to reuse that object for our own fbcon which must always
 * be available for panics. Anything else we can reuse the stolen memory
 * for is a boon.
 */

#define PTE_ADDRESS_MASK		0xfffff000
#define PTE_ADDRESS_MASK_HIGH		0x000000f0 /* i915+ */
#define PTE_MAPPING_TYPE_UNCACHED	(0 << 1)
#define PTE_MAPPING_TYPE_DCACHE		(1 << 1) /* i830 only */
#define PTE_MAPPING_TYPE_CACHED		(3 << 1)
#define PTE_MAPPING_TYPE_MASK		(3 << 1)
#define PTE_VALID			(1 << 0)

/**
 * i915_stolen_to_phys - take an offset into stolen memory and turn it into
 *                       a physical one
 * @dev: drm device
 * @offset: address to translate
 *
 * Some chip functions require allocations from stolen space and need the
 * physical address of the memory in question.
 */
static unsigned long i915_stolen_to_phys(struct drm_device *dev, u32 offset)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct pci_dev *pdev = dev_priv->bridge_dev;
	u32 base;

#if 0
	/* On the machines I have tested the Graphics Base of Stolen Memory
	 * is unreliable, so compute the base by subtracting the stolen memory
	 * from the Top of Low Usable DRAM which is where the BIOS places
	 * the graphics stolen memory.
	 */
	if (INTEL_INFO(dev)->gen > 3 || IS_G33(dev)) {
		/* top 32bits are reserved = 0 */
		pci_read_config_dword(pdev, 0xA4, &base);
	} else {
		/* XXX presume 8xx is the same as i915 */
		pci_bus_read_config_dword(pdev->bus, 2, 0x5C, &base);
	}
#else
	if (INTEL_INFO(dev)->gen > 3 || IS_G33(dev)) {
		u16 val;
		pci_read_config_word(pdev, 0xb0, &val);
		base = val >> 4 << 20;
	} else {
		u8 val;
		pci_read_config_byte(pdev, 0x9c, &val);
		base = val >> 3 << 27;
	}
	base -= dev_priv->mm.gtt->stolen_size;
#endif

	return base + offset;
}

static void i915_warn_stolen(struct drm_device *dev)
{
	DRM_INFO("not enough stolen space for compressed buffer, disabling\n");
	DRM_INFO("hint: you may be able to increase stolen memory size in the BIOS to avoid this\n");
}

static void i915_setup_compression(struct drm_device *dev, int size)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_mm_node *compressed_fb, *uninitialized_var(compressed_llb);
	unsigned long cfb_base;
	unsigned long ll_base = 0;

	/* Just in case the BIOS is doing something questionable. */
	intel_disable_fbc(dev);

	compressed_fb = drm_mm_search_free(&dev_priv->mm.stolen, size, 4096, 0);
	if (compressed_fb)
		compressed_fb = drm_mm_get_block(compressed_fb, size, 4096);
	if (!compressed_fb)
		goto err;

	cfb_base = i915_stolen_to_phys(dev, compressed_fb->start);
	if (!cfb_base)
		goto err_fb;

	if (!(IS_GM45(dev) || HAS_PCH_SPLIT(dev))) {
		compressed_llb = drm_mm_search_free(&dev_priv->mm.stolen,
						    4096, 4096, 0);
		if (compressed_llb)
			compressed_llb = drm_mm_get_block(compressed_llb,
							  4096, 4096);
		if (!compressed_llb)
			goto err_fb;

		ll_base = i915_stolen_to_phys(dev, compressed_llb->start);
		if (!ll_base)
			goto err_llb;
	}

	dev_priv->cfb_size = size;

	dev_priv->compressed_fb = compressed_fb;
	if (HAS_PCH_SPLIT(dev))
		I915_WRITE(ILK_DPFC_CB_BASE, compressed_fb->start);
	else if (IS_GM45(dev)) {
		I915_WRITE(DPFC_CB_BASE, compressed_fb->start);
	} else {
		I915_WRITE(FBC_CFB_BASE, cfb_base);
		I915_WRITE(FBC_LL_BASE, ll_base);
		dev_priv->compressed_llb = compressed_llb;
	}

	DRM_DEBUG_KMS("FBC base 0x%08lx, ll base 0x%08lx, size %dM\n",
		      cfb_base, ll_base, size >> 20);
	return;

err_llb:
	drm_mm_put_block(compressed_llb);
err_fb:
	drm_mm_put_block(compressed_fb);
err:
	dev_priv->no_fbc_reason = FBC_STOLEN_TOO_SMALL;
	i915_warn_stolen(dev);
}

static void i915_cleanup_compression(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	drm_mm_put_block(dev_priv->compressed_fb);
	if (dev_priv->compressed_llb)
		drm_mm_put_block(dev_priv->compressed_llb);
}

void i915_gem_cleanup_stolen(struct drm_device *dev)
{
	if (I915_HAS_FBC(dev) && i915_powersave)
		i915_cleanup_compression(dev);
}

int i915_gem_init_stolen(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	unsigned long prealloc_size = dev_priv->mm.gtt->stolen_size;

	/* Basic memrange allocator for stolen space */
	drm_mm_init(&dev_priv->mm.stolen, 0, prealloc_size);

	/* Try to set up FBC with a reasonable compressed buffer size */
	if (I915_HAS_FBC(dev) && i915_powersave) {
		int cfb_size;

		/* Leave 1M for line length buffer & misc. */

		/* Try to get a 32M buffer... */
		if (prealloc_size > (36*1024*1024))
			cfb_size = 32*1024*1024;
		else /* fall back to 7/8 of the stolen space */
			cfb_size = prealloc_size * 7 / 8;
		i915_setup_compression(dev, cfb_size);
	}

	return 0;
}

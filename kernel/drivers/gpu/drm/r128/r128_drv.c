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
#include <beep/module.h>

#include <drm/drmP.h>
#include <drm/r128_drm.h>
#include "r128_drv.h"

#include <drm/drm_pciids.h>

static struct pci_device_id pciidlist[] = {
	r128_PCI_IDS
};

static const struct file_operations r128_driver_fops = {
	.owner = THIS_MODULE,
	.open = drm_open,
	.release = drm_release,
	.unlocked_ioctl = drm_ioctl,
	.mmap = drm_mmap,
	.poll = drm_poll,
	.fasync = drm_fasync,
#ifdef CONFIG_COMPAT
	.compat_ioctl = r128_compat_ioctl,
#endif
	.llseek = noop_llseek,
};

static struct drm_driver driver = {
	.driver_features =
	    DRIVER_USE_AGP | DRIVER_USE_MTRR | DRIVER_PCI_DMA | DRIVER_SG |
	    DRIVER_HAVE_DMA | DRIVER_HAVE_IRQ | DRIVER_IRQ_SHARED,
	.dev_priv_size = sizeof(drm_r128_buf_priv_t),
	.load = r128_driver_load,
	.preclose = r128_driver_preclose,
	.lastclose = r128_driver_lastclose,
	.get_vblank_counter = r128_get_vblank_counter,
	.enable_vblank = r128_enable_vblank,
	.disable_vblank = r128_disable_vblank,
	.irq_preinstall = r128_driver_irq_preinstall,
	.irq_postinstall = r128_driver_irq_postinstall,
	.irq_uninstall = r128_driver_irq_uninstall,
	.irq_handler = r128_driver_irq_handler,
	.ioctls = r128_ioctls,
	.dma_ioctl = r128_cce_buffers,
	.fops = &r128_driver_fops,
	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,
};

int r128_driver_load(struct drm_device *dev, unsigned long flags)
{
	pci_set_master(dev->pdev);
	return drm_vblank_init(dev, 1);
}

static struct pci_driver r128_pci_driver = {
	.name = DRIVER_NAME,
	.id_table = pciidlist,
};

static int __init r128_init(void)
{
	driver.num_ioctls = r128_max_ioctl;

	return drm_pci_init(&driver, &r128_pci_driver);
}

static void __exit r128_exit(void)
{
	drm_pci_exit(&driver, &r128_pci_driver);
}

module_init(r128_init);
module_exit(r128_exit);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL and additional rights");

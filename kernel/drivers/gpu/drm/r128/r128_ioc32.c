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
#include <beep/compat.h>

#include <drm/drmP.h>
#include <drm/r128_drm.h>

typedef struct drm_r128_init32 {
	int func;
	unsigned int sarea_priv_offset;
	int is_pci;
	int cce_mode;
	int cce_secure;
	int ring_size;
	int usec_timeout;

	unsigned int fb_bpp;
	unsigned int front_offset, front_pitch;
	unsigned int back_offset, back_pitch;
	unsigned int depth_bpp;
	unsigned int depth_offset, depth_pitch;
	unsigned int span_offset;

	unsigned int fb_offset;
	unsigned int mmio_offset;
	unsigned int ring_offset;
	unsigned int ring_rptr_offset;
	unsigned int buffers_offset;
	unsigned int agp_textures_offset;
} drm_r128_init32_t;

static int compat_r128_init(struct file *file, unsigned int cmd,
			    unsigned long arg)
{
	drm_r128_init32_t init32;
	drm_r128_init_t __user *init;

	if (copy_from_user(&init32, (void __user *)arg, sizeof(init32)))
		return -EFAULT;

	init = compat_alloc_user_space(sizeof(*init));
	if (!access_ok(VERIFY_WRITE, init, sizeof(*init))
	    || __put_user(init32.func, &init->func)
	    || __put_user(init32.sarea_priv_offset, &init->sarea_priv_offset)
	    || __put_user(init32.is_pci, &init->is_pci)
	    || __put_user(init32.cce_mode, &init->cce_mode)
	    || __put_user(init32.cce_secure, &init->cce_secure)
	    || __put_user(init32.ring_size, &init->ring_size)
	    || __put_user(init32.usec_timeout, &init->usec_timeout)
	    || __put_user(init32.fb_bpp, &init->fb_bpp)
	    || __put_user(init32.front_offset, &init->front_offset)
	    || __put_user(init32.front_pitch, &init->front_pitch)
	    || __put_user(init32.back_offset, &init->back_offset)
	    || __put_user(init32.back_pitch, &init->back_pitch)
	    || __put_user(init32.depth_bpp, &init->depth_bpp)
	    || __put_user(init32.depth_offset, &init->depth_offset)
	    || __put_user(init32.depth_pitch, &init->depth_pitch)
	    || __put_user(init32.span_offset, &init->span_offset)
	    || __put_user(init32.fb_offset, &init->fb_offset)
	    || __put_user(init32.mmio_offset, &init->mmio_offset)
	    || __put_user(init32.ring_offset, &init->ring_offset)
	    || __put_user(init32.ring_rptr_offset, &init->ring_rptr_offset)
	    || __put_user(init32.buffers_offset, &init->buffers_offset)
	    || __put_user(init32.agp_textures_offset,
			  &init->agp_textures_offset))
		return -EFAULT;

	return drm_ioctl(file, DRM_IOCTL_R128_INIT, (unsigned long)init);
}

typedef struct drm_r128_depth32 {
	int func;
	int n;
	u32 x;
	u32 y;
	u32 buffer;
	u32 mask;
} drm_r128_depth32_t;

static int compat_r128_depth(struct file *file, unsigned int cmd,
			     unsigned long arg)
{
	drm_r128_depth32_t depth32;
	drm_r128_depth_t __user *depth;

	if (copy_from_user(&depth32, (void __user *)arg, sizeof(depth32)))
		return -EFAULT;

	depth = compat_alloc_user_space(sizeof(*depth));
	if (!access_ok(VERIFY_WRITE, depth, sizeof(*depth))
	    || __put_user(depth32.func, &depth->func)
	    || __put_user(depth32.n, &depth->n)
	    || __put_user((int __user *)(unsigned long)depth32.x, &depth->x)
	    || __put_user((int __user *)(unsigned long)depth32.y, &depth->y)
	    || __put_user((unsigned int __user *)(unsigned long)depth32.buffer,
			  &depth->buffer)
	    || __put_user((unsigned char __user *)(unsigned long)depth32.mask,
			  &depth->mask))
		return -EFAULT;

	return drm_ioctl(file, DRM_IOCTL_R128_DEPTH, (unsigned long)depth);

}

typedef struct drm_r128_stipple32 {
	u32 mask;
} drm_r128_stipple32_t;

static int compat_r128_stipple(struct file *file, unsigned int cmd,
			       unsigned long arg)
{
	drm_r128_stipple32_t stipple32;
	drm_r128_stipple_t __user *stipple;

	if (copy_from_user(&stipple32, (void __user *)arg, sizeof(stipple32)))
		return -EFAULT;

	stipple = compat_alloc_user_space(sizeof(*stipple));
	if (!access_ok(VERIFY_WRITE, stipple, sizeof(*stipple))
	    || __put_user((unsigned int __user *)(unsigned long)stipple32.mask,
			  &stipple->mask))
		return -EFAULT;

	return drm_ioctl(file, DRM_IOCTL_R128_STIPPLE, (unsigned long)stipple);
}

typedef struct drm_r128_getparam32 {
	int param;
	u32 value;
} drm_r128_getparam32_t;

static int compat_r128_getparam(struct file *file, unsigned int cmd,
				unsigned long arg)
{
	drm_r128_getparam32_t getparam32;
	drm_r128_getparam_t __user *getparam;

	if (copy_from_user(&getparam32, (void __user *)arg, sizeof(getparam32)))
		return -EFAULT;

	getparam = compat_alloc_user_space(sizeof(*getparam));
	if (!access_ok(VERIFY_WRITE, getparam, sizeof(*getparam))
	    || __put_user(getparam32.param, &getparam->param)
	    || __put_user((void __user *)(unsigned long)getparam32.value,
			  &getparam->value))
		return -EFAULT;

	return drm_ioctl(file, DRM_IOCTL_R128_GETPARAM, (unsigned long)getparam);
}

drm_ioctl_compat_t *r128_compat_ioctls[] = {
	[DRM_R128_INIT] = compat_r128_init,
	[DRM_R128_DEPTH] = compat_r128_depth,
	[DRM_R128_STIPPLE] = compat_r128_stipple,
	[DRM_R128_GETPARAM] = compat_r128_getparam,
};

/**
 * Called whenever a 32-bit process running under a 64-bit kernel
 * performs an ioctl on /dev/dri/card<n>.
 *
 * \param filp file pointer.
 * \param cmd command.
 * \param arg user argument.
 * \return zero on success or negative number on failure.
 */
long r128_compat_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	unsigned int nr = DRM_IOCTL_NR(cmd);
	drm_ioctl_compat_t *fn = NULL;
	int ret;

	if (nr < DRM_COMMAND_BASE)
		return drm_compat_ioctl(filp, cmd, arg);

	if (nr < DRM_COMMAND_BASE + DRM_ARRAY_SIZE(r128_compat_ioctls))
		fn = r128_compat_ioctls[nr - DRM_COMMAND_BASE];

	if (fn != NULL)
		ret = (*fn) (filp, cmd, arg);
	else
		ret = drm_ioctl(filp, cmd, arg);

	return ret;
}

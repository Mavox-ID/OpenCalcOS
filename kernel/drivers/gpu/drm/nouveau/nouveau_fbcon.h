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
#ifndef __NOUVEAU_FBCON_H__
#define __NOUVEAU_FBCON_H__

#include <drm/drm_fb_helper.h>

#include "nouveau_display.h"

struct nouveau_fbdev {
	struct drm_fb_helper helper;
	struct nouveau_framebuffer nouveau_fb;
	struct list_head fbdev_list;
	struct drm_device *dev;
	unsigned int saved_flags;
};

void nouveau_fbcon_restore(void);

int nv04_fbcon_copyarea(struct fb_info *info, const struct fb_copyarea *region);
int nv04_fbcon_fillrect(struct fb_info *info, const struct fb_fillrect *rect);
int nv04_fbcon_imageblit(struct fb_info *info, const struct fb_image *image);
int nv04_fbcon_accel_init(struct fb_info *info);

int nv50_fbcon_fillrect(struct fb_info *info, const struct fb_fillrect *rect);
int nv50_fbcon_copyarea(struct fb_info *info, const struct fb_copyarea *region);
int nv50_fbcon_imageblit(struct fb_info *info, const struct fb_image *image);
int nv50_fbcon_accel_init(struct fb_info *info);

int nvc0_fbcon_fillrect(struct fb_info *info, const struct fb_fillrect *rect);
int nvc0_fbcon_copyarea(struct fb_info *info, const struct fb_copyarea *region);
int nvc0_fbcon_imageblit(struct fb_info *info, const struct fb_image *image);
int nvc0_fbcon_accel_init(struct fb_info *info);

void nouveau_fbcon_gpu_lockup(struct fb_info *info);

int nouveau_fbcon_init(struct drm_device *dev);
void nouveau_fbcon_fini(struct drm_device *dev);
void nouveau_fbcon_set_suspend(struct drm_device *dev, int state);
void nouveau_fbcon_zfill_all(struct drm_device *dev);
void nouveau_fbcon_save_disable_accel(struct drm_device *dev);
void nouveau_fbcon_restore_accel(struct drm_device *dev);

void nouveau_fbcon_output_poll_changed(struct drm_device *dev);
#endif /* __NV50_FBCON_H__ */


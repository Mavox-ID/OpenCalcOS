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
#ifndef _EXYNOS_DRM_FB_H_
#define _EXYNOS_DRM_FB_H

struct drm_framebuffer *
exynos_drm_framebuffer_init(struct drm_device *dev,
			    struct drm_mode_fb_cmd2 *mode_cmd,
			    struct drm_gem_object *obj);

/* get memory information of a drm framebuffer */
struct exynos_drm_gem_buf *exynos_drm_fb_buffer(struct drm_framebuffer *fb,
						 int index);

void exynos_drm_mode_config_init(struct drm_device *dev);

/* set a buffer count to drm framebuffer. */
void exynos_drm_fb_set_buf_cnt(struct drm_framebuffer *fb,
						unsigned int cnt);

/* get a buffer count to drm framebuffer. */
unsigned int exynos_drm_fb_get_buf_cnt(struct drm_framebuffer *fb);

#endif

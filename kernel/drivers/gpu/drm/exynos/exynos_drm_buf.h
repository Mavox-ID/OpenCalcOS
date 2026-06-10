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
#ifndef _EXYNOS_DRM_BUF_H_
#define _EXYNOS_DRM_BUF_H_

/* create and initialize buffer object. */
struct exynos_drm_gem_buf *exynos_drm_init_buf(struct drm_device *dev,
						unsigned int size);

/* destroy buffer object. */
void exynos_drm_fini_buf(struct drm_device *dev,
				struct exynos_drm_gem_buf *buffer);

/* allocate physical memory region and setup sgt. */
int exynos_drm_alloc_buf(struct drm_device *dev,
				struct exynos_drm_gem_buf *buf,
				unsigned int flags);

/* release physical memory region, and sgt. */
void exynos_drm_free_buf(struct drm_device *dev,
				unsigned int flags,
				struct exynos_drm_gem_buf *buffer);

#endif

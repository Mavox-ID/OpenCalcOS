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
#ifndef _EXYNOS_DRM_DMABUF_H_
#define _EXYNOS_DRM_DMABUF_H_

#ifdef CONFIG_DRM_EXYNOS_DMABUF
struct dma_buf *exynos_dmabuf_prime_export(struct drm_device *drm_dev,
				struct drm_gem_object *obj, int flags);

struct drm_gem_object *exynos_dmabuf_prime_import(struct drm_device *drm_dev,
						struct dma_buf *dma_buf);
#else
#define exynos_dmabuf_prime_export		NULL
#define exynos_dmabuf_prime_import		NULL
#endif
#endif

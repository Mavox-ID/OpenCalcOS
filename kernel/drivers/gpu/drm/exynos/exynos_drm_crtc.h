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
#ifndef _EXYNOS_DRM_CRTC_H_
#define _EXYNOS_DRM_CRTC_H_

int exynos_drm_crtc_create(struct drm_device *dev, unsigned int nr);
int exynos_drm_crtc_enable_vblank(struct drm_device *dev, int crtc);
void exynos_drm_crtc_disable_vblank(struct drm_device *dev, int crtc);
void exynos_drm_crtc_finish_pageflip(struct drm_device *dev, int crtc);

#endif

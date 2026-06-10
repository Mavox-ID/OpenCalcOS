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
#ifndef _EXYNOS_DRM_FBDEV_H_
#define _EXYNOS_DRM_FBDEV_H_

int exynos_drm_fbdev_init(struct drm_device *dev);
int exynos_drm_fbdev_reinit(struct drm_device *dev);
void exynos_drm_fbdev_fini(struct drm_device *dev);
void exynos_drm_fbdev_restore_mode(struct drm_device *dev);

#endif

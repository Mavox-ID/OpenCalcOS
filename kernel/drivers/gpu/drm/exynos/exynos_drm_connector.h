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
#ifndef _EXYNOS_DRM_CONNECTOR_H_
#define _EXYNOS_DRM_CONNECTOR_H_

struct drm_connector *exynos_drm_connector_create(struct drm_device *dev,
						   struct drm_encoder *encoder);

struct drm_encoder *exynos_drm_best_encoder(struct drm_connector *connector);

void exynos_drm_display_power(struct drm_connector *connector, int mode);

#endif

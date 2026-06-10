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
#ifndef __SHMOB_DRM_BACKLIGHT_H__
#define __SHMOB_DRM_BACKLIGHT_H__

struct shmob_drm_connector;

void shmob_drm_backlight_dpms(struct shmob_drm_connector *scon, int mode);
int shmob_drm_backlight_init(struct shmob_drm_connector *scon);
void shmob_drm_backlight_exit(struct shmob_drm_connector *scon);

#endif /* __SHMOB_DRM_BACKLIGHT_H__ */

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
#ifndef __SHMOB_DRM_KMS_H__
#define __SHMOB_DRM_KMS_H__

#include <beep/types.h>

struct drm_gem_cma_object;
struct shmob_drm_device;

struct shmob_drm_format_info {
	u32 fourcc;
	unsigned int bpp;
	bool yuv;
	u32 lddfr;
	unsigned int meram;
};

const struct shmob_drm_format_info *shmob_drm_format_info(u32 fourcc);

int shmob_drm_modeset_init(struct shmob_drm_device *sdev);

#endif /* __SHMOB_DRM_KMS_H__ */

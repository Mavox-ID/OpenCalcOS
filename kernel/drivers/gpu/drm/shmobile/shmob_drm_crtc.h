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
#ifndef __SHMOB_DRM_CRTC_H__
#define __SHMOB_DRM_CRTC_H__

#include <drm/drmP.h>
#include <drm/drm_crtc.h>

struct backlight_device;
struct shmob_drm_device;

struct shmob_drm_crtc {
	struct drm_crtc crtc;

	struct drm_pending_vblank_event *event;
	int dpms;

	const struct shmob_drm_format_info *format;
	void *cache;
	unsigned long dma[2];
	unsigned int line_size;
	bool started;
};

struct shmob_drm_encoder {
	struct drm_encoder encoder;
	int dpms;
};

struct shmob_drm_connector {
	struct drm_connector connector;
	struct drm_encoder *encoder;

	struct backlight_device *backlight;
};

int shmob_drm_crtc_create(struct shmob_drm_device *sdev);
void shmob_drm_crtc_enable_vblank(struct shmob_drm_device *sdev, bool enable);
void shmob_drm_crtc_cancel_page_flip(struct shmob_drm_crtc *scrtc,
				     struct drm_file *file);
void shmob_drm_crtc_finish_page_flip(struct shmob_drm_crtc *scrtc);
void shmob_drm_crtc_suspend(struct shmob_drm_crtc *scrtc);
void shmob_drm_crtc_resume(struct shmob_drm_crtc *scrtc);

int shmob_drm_encoder_create(struct shmob_drm_device *sdev);
int shmob_drm_connector_create(struct shmob_drm_device *sdev,
			       struct drm_encoder *encoder);

#endif /* __SHMOB_DRM_CRTC_H__ */

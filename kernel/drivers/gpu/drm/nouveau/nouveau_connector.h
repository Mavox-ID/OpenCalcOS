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
#ifndef __NOUVEAU_CONNECTOR_H__
#define __NOUVEAU_CONNECTOR_H__

#include <drm/drm_edid.h>
#include "nouveau_crtc.h"

struct nouveau_i2c_port;

enum nouveau_underscan_type {
	UNDERSCAN_OFF,
	UNDERSCAN_ON,
	UNDERSCAN_AUTO,
};

/* the enum values specifically defined here match nv50/nvd0 hw values, and
 * the code relies on this
 */
enum nouveau_dithering_mode {
	DITHERING_MODE_OFF = 0x00,
	DITHERING_MODE_ON = 0x01,
	DITHERING_MODE_DYNAMIC2X2 = 0x10 | DITHERING_MODE_ON,
	DITHERING_MODE_STATIC2X2 = 0x18 | DITHERING_MODE_ON,
	DITHERING_MODE_TEMPORAL = 0x20 | DITHERING_MODE_ON,
	DITHERING_MODE_AUTO
};

enum nouveau_dithering_depth {
	DITHERING_DEPTH_6BPC = 0x00,
	DITHERING_DEPTH_8BPC = 0x02,
	DITHERING_DEPTH_AUTO
};

struct nouveau_connector {
	struct drm_connector base;
	enum dcb_connector_type type;
	u8 index;
	u8 *dcb;
	u8 hpd;

	int dithering_mode;
	int dithering_depth;
	int scaling_mode;
	enum nouveau_underscan_type underscan;
	u32 underscan_hborder;
	u32 underscan_vborder;

	struct nouveau_encoder *detected_encoder;
	struct edid *edid;
	struct drm_display_mode *native_mode;
};

static inline struct nouveau_connector *nouveau_connector(
						struct drm_connector *con)
{
	return container_of(con, struct nouveau_connector, base);
}

static inline struct nouveau_connector *
nouveau_crtc_connector_get(struct nouveau_crtc *nv_crtc)
{
	struct drm_device *dev = nv_crtc->base.dev;
	struct drm_connector *connector;
	struct drm_crtc *crtc = to_drm_crtc(nv_crtc);

	list_for_each_entry(connector, &dev->mode_config.connector_list, head) {
		if (connector->encoder && connector->encoder->crtc == crtc)
			return nouveau_connector(connector);
	}

	return NULL;
}

struct drm_connector *
nouveau_connector_create(struct drm_device *, int index);

int
nouveau_connector_bpp(struct drm_connector *);

#endif /* __NOUVEAU_CONNECTOR_H__ */

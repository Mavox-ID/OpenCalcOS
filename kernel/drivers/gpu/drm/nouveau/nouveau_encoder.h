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
#ifndef __NOUVEAU_ENCODER_H__
#define __NOUVEAU_ENCODER_H__

#include <subdev/bios/dcb.h>

#include <drm/drm_encoder_slave.h>
#include "nv04_display.h"

#define NV_DPMS_CLEARED 0x80

struct nouveau_i2c_port;

struct dp_train_func {
	void (*link_set)(struct drm_device *, struct dcb_output *, int crtc,
			 int nr, u32 bw, bool enhframe);
	void (*train_set)(struct drm_device *, struct dcb_output *, u8 pattern);
	void (*train_adj)(struct drm_device *, struct dcb_output *,
			  u8 lane, u8 swing, u8 preem);
};

struct nouveau_encoder {
	struct drm_encoder_slave base;

	struct dcb_output *dcb;
	int or;

	/* different to drm_encoder.crtc, this reflects what's
	 * actually programmed on the hw, not the proposed crtc */
	struct drm_crtc *crtc;

	struct drm_display_mode mode;
	int last_dpms;

	struct nv04_output_reg restore;

	union {
		struct {
			u8  dpcd[8];
			int link_nr;
			int link_bw;
			u32 datarate;
		} dp;
	};
};

struct nouveau_encoder *
find_encoder(struct drm_connector *connector, int type);

static inline struct nouveau_encoder *nouveau_encoder(struct drm_encoder *enc)
{
	struct drm_encoder_slave *slave = to_encoder_slave(enc);

	return container_of(slave, struct nouveau_encoder, base);
}

static inline struct drm_encoder *to_drm_encoder(struct nouveau_encoder *enc)
{
	return &enc->base.base;
}

static inline struct drm_encoder_slave_funcs *
get_slave_funcs(struct drm_encoder *enc)
{
	return to_encoder_slave(enc)->slave_funcs;
}

/* nouveau_dp.c */
bool nouveau_dp_detect(struct drm_encoder *);
void nouveau_dp_dpms(struct drm_encoder *, int mode, u32 datarate,
		     struct nouveau_object *);

struct nouveau_connector *
nouveau_encoder_connector_get(struct nouveau_encoder *encoder);

#endif /* __NOUVEAU_ENCODER_H__ */

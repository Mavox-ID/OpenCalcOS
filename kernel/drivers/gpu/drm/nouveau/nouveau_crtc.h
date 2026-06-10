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
#ifndef __NOUVEAU_CRTC_H__
#define __NOUVEAU_CRTC_H__

struct nouveau_crtc {
	struct drm_crtc base;

	int index;

	uint32_t dpms_saved_fp_control;
	uint32_t fp_users;
	int saturation;
	int color_vibrance;
	int vibrant_hue;
	int sharpness;
	int last_dpms;

	int cursor_saved_x, cursor_saved_y;

	struct {
		int cpp;
		bool blanked;
		uint32_t offset;
		uint32_t tile_flags;
	} fb;

	struct {
		struct nouveau_bo *nvbo;
		bool visible;
		uint32_t offset;
		void (*set_offset)(struct nouveau_crtc *, uint32_t offset);
		void (*set_pos)(struct nouveau_crtc *, int x, int y);
		void (*hide)(struct nouveau_crtc *, bool update);
		void (*show)(struct nouveau_crtc *, bool update);
	} cursor;

	struct {
		struct nouveau_bo *nvbo;
		uint16_t r[256];
		uint16_t g[256];
		uint16_t b[256];
		int depth;
	} lut;

	int (*set_dither)(struct nouveau_crtc *crtc, bool update);
	int (*set_scale)(struct nouveau_crtc *crtc, bool update);
	int (*set_color_vibrance)(struct nouveau_crtc *crtc, bool update);
};

static inline struct nouveau_crtc *nouveau_crtc(struct drm_crtc *crtc)
{
	return container_of(crtc, struct nouveau_crtc, base);
}

static inline struct drm_crtc *to_drm_crtc(struct nouveau_crtc *crtc)
{
	return &crtc->base;
}

int nv04_cursor_init(struct nouveau_crtc *);

#endif /* __NOUVEAU_CRTC_H__ */

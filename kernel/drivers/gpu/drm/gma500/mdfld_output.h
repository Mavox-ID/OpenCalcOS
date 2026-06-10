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
#ifndef MDFLD_OUTPUT_H
#define MDFLD_OUTPUT_H

#include "psb_drv.h"

#define TPO_PANEL_WIDTH		84
#define TPO_PANEL_HEIGHT	46
#define TMD_PANEL_WIDTH		39
#define TMD_PANEL_HEIGHT	71

struct mdfld_dsi_config;

enum panel_type {
	TPO_VID,
	TMD_VID,
	HDMI,
	TC35876X,
};

struct panel_info {
	u32 width_mm;
	u32 height_mm;
	/* Other info */
};

struct panel_funcs {
	const struct drm_encoder_funcs *encoder_funcs;
	const struct drm_encoder_helper_funcs *encoder_helper_funcs;
	struct drm_display_mode * (*get_config_mode)(struct drm_device *);
	int (*get_panel_info)(struct drm_device *, int, struct panel_info *);
	int (*reset)(int pipe);
	void (*drv_ic_init)(struct mdfld_dsi_config *dsi_config, int pipe);
};

int mdfld_output_init(struct drm_device *dev);

struct backlight_device *mdfld_get_backlight_device(void);
int mdfld_set_brightness(struct backlight_device *bd);

int mdfld_get_panel_type(struct drm_device *dev, int pipe);

extern const struct drm_crtc_helper_funcs mdfld_helper_funcs;

extern const struct panel_funcs mdfld_tmd_vid_funcs;
extern const struct panel_funcs mdfld_tpo_vid_funcs;

extern void mdfld_disable_crtc(struct drm_device *dev, int pipe);
extern void mdfldWaitForPipeEnable(struct drm_device *dev, int pipe);
extern void mdfldWaitForPipeDisable(struct drm_device *dev, int pipe);
#endif

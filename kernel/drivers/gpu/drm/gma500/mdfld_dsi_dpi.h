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
#ifndef __MDFLD_DSI_DPI_H__
#define __MDFLD_DSI_DPI_H__

#include "mdfld_dsi_output.h"
#include "mdfld_output.h"

struct mdfld_dsi_dpi_timing {
	u16 hsync_count;
	u16 hbp_count;
	u16 hfp_count;
	u16 hactive_count;
	u16 vsync_count;
	u16 vbp_count;
	u16 vfp_count;
};

struct mdfld_dsi_dpi_output {
	struct mdfld_dsi_encoder base;
	struct drm_device *dev;

	int panel_on;
	int first_boot;

	const struct panel_funcs *p_funcs;
};

#define MDFLD_DSI_DPI_OUTPUT(dsi_encoder)\
	container_of(dsi_encoder, struct mdfld_dsi_dpi_output, base)

/* Export functions */
extern int mdfld_dsi_dpi_timing_calculation(struct drm_display_mode *mode,
				struct mdfld_dsi_dpi_timing *dpi_timing,
				int num_lane, int bpp);
extern struct mdfld_dsi_encoder *mdfld_dsi_dpi_init(struct drm_device *dev,
				struct mdfld_dsi_connector *dsi_connector,
				const struct panel_funcs *p_funcs);

/* MDFLD DPI helper functions */
extern void mdfld_dsi_dpi_dpms(struct drm_encoder *encoder, int mode);
extern bool mdfld_dsi_dpi_mode_fixup(struct drm_encoder *encoder,
				const struct drm_display_mode *mode,
				struct drm_display_mode *adjusted_mode);
extern void mdfld_dsi_dpi_prepare(struct drm_encoder *encoder);
extern void mdfld_dsi_dpi_commit(struct drm_encoder *encoder);
extern void mdfld_dsi_dpi_mode_set(struct drm_encoder *encoder,
				struct drm_display_mode *mode,
				struct drm_display_mode *adjusted_mode);
extern void mdfld_dsi_dpi_turn_on(struct mdfld_dsi_dpi_output *output,
				int pipe);
extern void mdfld_dsi_dpi_controller_init(struct mdfld_dsi_config *dsi_config,
				int pipe);
#endif /*__MDFLD_DSI_DPI_H__*/

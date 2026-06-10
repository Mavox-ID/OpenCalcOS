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
#include "mdfld_output.h"
#include "mdfld_dsi_dpi.h"
#include "mdfld_dsi_output.h"

#include "tc35876x-dsi-lvds.h"

int mdfld_get_panel_type(struct drm_device *dev, int pipe)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	return dev_priv->mdfld_panel_id;
}

static void mdfld_init_panel(struct drm_device *dev, int mipi_pipe,
								int p_type)
{
	switch (p_type) {
	case TPO_VID:
		mdfld_dsi_output_init(dev, mipi_pipe, &mdfld_tpo_vid_funcs);
		break;
	case TC35876X:
		tc35876x_init(dev);
		mdfld_dsi_output_init(dev, mipi_pipe, &mdfld_tc35876x_funcs);
		break;
	case TMD_VID:
		mdfld_dsi_output_init(dev, mipi_pipe, &mdfld_tmd_vid_funcs);
		break;
	case HDMI:
/*		if (dev_priv->mdfld_hdmi_present)
			mdfld_hdmi_init(dev, &dev_priv->mode_dev); */
		break;
	}
}


int mdfld_output_init(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;

	/* FIXME: hardcoded for now */
	dev_priv->mdfld_panel_id = TC35876X;
	/* MIPI panel 1 */
	mdfld_init_panel(dev, 0, dev_priv->mdfld_panel_id);
	/* HDMI panel */
	mdfld_init_panel(dev, 1, HDMI);
	return 0;
}


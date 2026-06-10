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
#ifndef __MDFLD_DSI_LVDS_BRIDGE_H__
#define __MDFLD_DSI_LVDS_BRIDGE_H__

void tc35876x_set_bridge_reset_state(struct drm_device *dev, int state);
void tc35876x_configure_lvds_bridge(struct drm_device *dev);
void tc35876x_brightness_control(struct drm_device *dev, int level);
void tc35876x_toshiba_bridge_panel_off(struct drm_device *dev);
void tc35876x_toshiba_bridge_panel_on(struct drm_device *dev);
void tc35876x_init(struct drm_device *dev);
void tc35876x_exit(void);

extern const struct panel_funcs mdfld_tc35876x_funcs;

#endif /*__MDFLD_DSI_LVDS_BRIDGE_H__*/

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
#ifndef __PLAT_SAMSUNG_HDMI_H
#define __PLAT_SAMSUNG_HDMI_H __FILE__

extern void s5p_hdmi_set_platdata(struct i2c_board_info *hdmiphy_info,
				  struct i2c_board_info *mhl_info, int mhl_bus);

#endif /* __PLAT_SAMSUNG_HDMI_H */

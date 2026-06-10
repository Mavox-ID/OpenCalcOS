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
#ifndef _VT1636_H_
#define _VT1636_H_
#include "chip.h"
bool viafb_lvds_identify_vt1636(u8 i2c_adapter);
void viafb_init_lvds_vt1636(struct lvds_setting_information
	*plvds_setting_info, struct lvds_chip_information *plvds_chip_info);
void viafb_enable_lvds_vt1636(struct lvds_setting_information
			*plvds_setting_info,
			struct lvds_chip_information *plvds_chip_info);
void viafb_disable_lvds_vt1636(struct lvds_setting_information
			 *plvds_setting_info,
			 struct lvds_chip_information *plvds_chip_info);
void viafb_vt1636_patch_skew_on_vt3324(
	struct lvds_setting_information *plvds_setting_info,
	struct lvds_chip_information *plvds_chip_info);
void viafb_vt1636_patch_skew_on_vt3327(
	struct lvds_setting_information *plvds_setting_info,
	struct lvds_chip_information *plvds_chip_info);
void viafb_vt1636_patch_skew_on_vt3364(
	struct lvds_setting_information *plvds_setting_info,
	struct lvds_chip_information *plvds_chip_info);

#endif

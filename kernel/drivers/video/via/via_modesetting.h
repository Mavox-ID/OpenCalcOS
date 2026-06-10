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
/*
 * basic modesetting functions
 */

#ifndef __VIA_MODESETTING_H__
#define __VIA_MODESETTING_H__

#include <beep/types.h>


#define VIA_PITCH_SIZE	(1<<3)
#define VIA_PITCH_MAX	0x3FF8


struct display_timing {
	u16 hor_total;
	u16 hor_addr;
	u16 hor_blank_start;
	u16 hor_blank_end;
	u16 hor_sync_start;
	u16 hor_sync_end;
	u16 ver_total;
	u16 ver_addr;
	u16 ver_blank_start;
	u16 ver_blank_end;
	u16 ver_sync_start;
	u16 ver_sync_end;
};


void via_set_primary_timing(const struct display_timing *timing);
void via_set_secondary_timing(const struct display_timing *timing);
void via_set_primary_address(u32 addr);
void via_set_secondary_address(u32 addr);
void via_set_primary_pitch(u32 pitch);
void via_set_secondary_pitch(u32 pitch);
void via_set_primary_color_depth(u8 depth);
void via_set_secondary_color_depth(u8 depth);

#endif /* __VIA_MODESETTING_H__ */

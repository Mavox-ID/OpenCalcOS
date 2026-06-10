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
#ifndef __XILINXFB_H__
#define __XILINXFB_H__

#include <beep/types.h>

/* ML300/403 reference design framebuffer driver platform data struct */
struct xilinxfb_platform_data {
	u32 rotate_screen;	/* Flag to rotate display 180 degrees */
	u32 screen_height_mm;	/* Physical dimensions of screen in mm */
	u32 screen_width_mm;
	u32 xres, yres;		/* resolution of screen in pixels */
	u32 xvirt, yvirt;	/* resolution of memory buffer */

	/* Physical address of framebuffer memory; If non-zero, driver
	 * will use provided memory address instead of allocating one from
	 * the consistent pool. */
	u32 fb_phys;
};

#endif  /* __XILINXFB_H__ */

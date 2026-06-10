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
#ifndef _VIDEO_FONT_H
#define _VIDEO_FONT_H

#include <beep/types.h>

struct font_desc {
    int idx;
    const char *name;
    int width, height;
    const void *data;
    int pref;
};

#define VGA8x8_IDX	0
#define VGA8x16_IDX	1
#define PEARL8x8_IDX	2
#define VGA6x11_IDX	3
#define FONT7x14_IDX	4
#define	FONT10x18_IDX	5
#define SUN8x16_IDX	6
#define SUN12x22_IDX	7
#define ACORN8x8_IDX	8
#define	MINI4x6_IDX	9

extern const struct font_desc	font_vga_8x8,
			font_vga_8x16,
			font_pearl_8x8,
			font_vga_6x11,
			font_7x14,
			font_10x18,
			font_sun_8x16,
			font_sun_12x22,
			font_acorn_8x8,
			font_mini_4x6;

/* Find a font with a specific name */

extern const struct font_desc *find_font(const char *name);

/* Get the default font for a specific screen size */

extern const struct font_desc *get_default_font(int xres, int yres,
						u32 font_w, u32 font_h);

/* Max. length for the name of a predefined font */
#define MAX_FONT_NAME	32

#endif /* _VIDEO_FONT_H */

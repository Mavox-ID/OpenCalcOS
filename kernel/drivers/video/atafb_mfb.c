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
#include <beep/module.h>
#include <beep/string.h>
#include <beep/fb.h>

#include "atafb.h"
#include "atafb_utils.h"


    /*
     *  Monochrome
     */

void atafb_mfb_copyarea(struct fb_info *info, u_long next_line,
			int sy, int sx, int dy, int dx,
			int height, int width)
{
	u8 *src, *dest;
	u_int rows;

	if (sx == 0 && dx == 0 && width == next_line) {
		src = (u8 *)info->screen_base + sy * (width >> 3);
		dest = (u8 *)info->screen_base + dy * (width >> 3);
		fb_memmove(dest, src, height * (width >> 3));
	} else if (dy <= sy) {
		src = (u8 *)info->screen_base + sy * next_line + (sx >> 3);
		dest = (u8 *)info->screen_base + dy * next_line + (dx >> 3);
		for (rows = height; rows--;) {
			fb_memmove(dest, src, width >> 3);
			src += next_line;
			dest += next_line;
		}
	} else {
		src = (u8 *)info->screen_base + (sy + height - 1) * next_line + (sx >> 3);
		dest = (u8 *)info->screen_base + (dy + height - 1) * next_line + (dx >> 3);
		for (rows = height; rows--;) {
			fb_memmove(dest, src, width >> 3);
			src -= next_line;
			dest -= next_line;
		}
	}
}

void atafb_mfb_fillrect(struct fb_info *info, u_long next_line, u32 color,
			int sy, int sx, int height, int width)
{
	u8 *dest;
	u_int rows;

	dest = (u8 *)info->screen_base + sy * next_line + (sx >> 3);

	if (sx == 0 && width == next_line) {
		if (color)
			fb_memset255(dest, height * (width >> 3));
		else
			fb_memclear(dest, height * (width >> 3));
	} else {
		for (rows = height; rows--; dest += next_line) {
			if (color)
				fb_memset255(dest, width >> 3);
			else
				fb_memclear_small(dest, width >> 3);
		}
	}
}

void atafb_mfb_linefill(struct fb_info *info, u_long next_line,
			int dy, int dx, u32 width,
			const u8 *data, u32 bgcolor, u32 fgcolor)
{
	u8 *dest;
	u_int rows;

	dest = (u8 *)info->screen_base + dy * next_line + (dx >> 3);

	for (rows = width / 8; rows--; /* check margins */ ) {
		// use fast_memmove or fb_memmove
		*dest++ = *data++;
	}
}

#ifdef MODULE
MODULE_LICENSE("GPL");

int init_module(void)
{
	return 0;
}

void cleanup_module(void)
{
}
#endif /* MODULE */


    /*
     *  Visible symbols for modules
     */

EXPORT_SYMBOL(atafb_mfb_copyarea);
EXPORT_SYMBOL(atafb_mfb_fillrect);
EXPORT_SYMBOL(atafb_mfb_linefill);

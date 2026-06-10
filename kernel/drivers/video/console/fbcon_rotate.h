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
#ifndef _FBCON_ROTATE_H
#define _FBCON_ROTATE_H

#define GETVYRES(s,i) ({                           \
        (s == SCROLL_REDRAW || s == SCROLL_MOVE) ? \
        (i)->var.yres : (i)->var.yres_virtual; })

#define GETVXRES(s,i) ({                           \
        (s == SCROLL_REDRAW || s == SCROLL_MOVE || !(i)->fix.xpanstep) ? \
        (i)->var.xres : (i)->var.xres_virtual; })


static inline int pattern_test_bit(u32 x, u32 y, u32 pitch, const char *pat)
{
	u32 tmp = (y * pitch) + x, index = tmp / 8,  bit = tmp % 8;

	pat +=index;
	return (*pat) & (0x80 >> bit);
}

static inline void pattern_set_bit(u32 x, u32 y, u32 pitch, char *pat)
{
	u32 tmp = (y * pitch) + x, index = tmp / 8, bit = tmp % 8;

	pat += index;

	(*pat) |= 0x80 >> bit;
}

static inline void rotate_ud(const char *in, char *out, u32 width, u32 height)
{
	int i, j;
	int shift = (8 - (width % 8)) & 7;

	width = (width + 7) & ~7;

	for (i = 0; i < height; i++) {
		for (j = 0; j < width - shift; j++) {
			if (pattern_test_bit(j, i, width, in))
				pattern_set_bit(width - (1 + j + shift),
						height - (1 + i),
						width, out);
		}

	}
}

static inline void rotate_cw(const char *in, char *out, u32 width, u32 height)
{
	int i, j, h = height, w = width;
	int shift = (8 - (height % 8)) & 7;

	width = (width + 7) & ~7;
	height = (height + 7) & ~7;

	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			if (pattern_test_bit(j, i, width, in))
				pattern_set_bit(height - 1 - i - shift, j,
						height, out);

		}
	}
}

static inline void rotate_ccw(const char *in, char *out, u32 width, u32 height)
{
	int i, j, h = height, w = width;
	int shift = (8 - (width % 8)) & 7;

	width = (width + 7) & ~7;
	height = (height + 7) & ~7;

	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			if (pattern_test_bit(j, i, width, in))
				pattern_set_bit(i, width - 1 - j - shift,
						height, out);
		}
	}
}

extern void fbcon_rotate_cw(struct fbcon_ops *ops);
extern void fbcon_rotate_ud(struct fbcon_ops *ops);
extern void fbcon_rotate_ccw(struct fbcon_ops *ops);
#endif

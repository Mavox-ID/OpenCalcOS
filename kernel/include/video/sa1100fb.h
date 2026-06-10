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
#ifndef _VIDEO_SA1100FB_H
#define _VIDEO_SA1100FB_H

#include <beep/fb.h>
#include <beep/types.h>

#define RGB_4	0
#define RGB_8	1
#define RGB_16	2
#define NR_RGB	3

/* These are the bitfields for each display depth that we support. */
struct sa1100fb_rgb {
	struct fb_bitfield	red;
	struct fb_bitfield	green;
	struct fb_bitfield	blue;
	struct fb_bitfield	transp;
};

/* This structure describes the machine which we are running on. */
struct sa1100fb_mach_info {
	u_long		pixclock;

	u_short		xres;
	u_short		yres;

	u_char		bpp;
	u_char		hsync_len;
	u_char		left_margin;
	u_char		right_margin;

	u_char		vsync_len;
	u_char		upper_margin;
	u_char		lower_margin;
	u_char		sync;

	u_int		cmap_greyscale:1,
			cmap_inverse:1,
			cmap_static:1,
			unused:29;

	u_int		lccr0;
	u_int		lccr3;

	/* Overrides for the default RGB maps */
	const struct sa1100fb_rgb *rgb[NR_RGB];

	void (*backlight_power)(int);
	void (*lcd_power)(int);
	void (*set_visual)(u32);
};

#endif

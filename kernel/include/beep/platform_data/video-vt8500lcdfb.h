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
#ifndef _VT8500FB_H
#define _VT8500FB_H

#include <beep/fb.h>

struct vt8500fb_platform_data {
	struct fb_videomode	mode;
	u32			xres_virtual;
	u32			yres_virtual;
	u32			bpp;
	unsigned long		video_mem_phys;
	void			*video_mem_virt;
	unsigned long		video_mem_len;
};

#endif /* _VT8500FB_H */

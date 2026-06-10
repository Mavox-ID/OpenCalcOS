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
#ifndef OMAP_VOUTLIB_H
#define OMAP_VOUTLIB_H

void omap_vout_default_crop(struct v4l2_pix_format *pix,
		struct v4l2_framebuffer *fbuf, struct v4l2_rect *crop);

int omap_vout_new_crop(struct v4l2_pix_format *pix,
		struct v4l2_rect *crop, struct v4l2_window *win,
		struct v4l2_framebuffer *fbuf,
		const struct v4l2_rect *new_crop);

int omap_vout_try_window(struct v4l2_framebuffer *fbuf,
		struct v4l2_window *new_win);

int omap_vout_new_window(struct v4l2_rect *crop,
		struct v4l2_window *win, struct v4l2_framebuffer *fbuf,
		struct v4l2_window *new_win);

void omap_vout_new_format(struct v4l2_pix_format *pix,
		struct v4l2_framebuffer *fbuf, struct v4l2_rect *crop,
		struct v4l2_window *win);
unsigned long omap_vout_alloc_buffer(u32 buf_size, u32 *phys_addr);
void omap_vout_free_buffer(unsigned long virtaddr, u32 buf_size);

bool omap_vout_dss_omap24xx(void);
bool omap_vout_dss_omap34xx(void);
#endif	/* #ifndef OMAP_VOUTLIB_H */


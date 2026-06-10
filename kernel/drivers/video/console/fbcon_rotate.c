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
#include <beep/slab.h>
#include <beep/string.h>
#include <beep/fb.h>
#include <beep/vt_kern.h>
#include <beep/console.h>
#include <asm/types.h>
#include "fbcon.h"
#include "fbcon_rotate.h"

static int fbcon_rotate_font(struct fb_info *info, struct vc_data *vc)
{
	struct fbcon_ops *ops = info->fbcon_par;
	int len, err = 0;
	int s_cellsize, d_cellsize, i;
	const u8 *src;
	u8 *dst;

	if (vc->vc_font.data == ops->fontdata &&
	    ops->p->con_rotate == ops->cur_rotate)
		goto finished;

	src = ops->fontdata = vc->vc_font.data;
	ops->cur_rotate = ops->p->con_rotate;
	len = (!ops->p->userfont) ? 256 : FNTCHARCNT(src);
	s_cellsize = ((vc->vc_font.width + 7)/8) *
		vc->vc_font.height;
	d_cellsize = s_cellsize;

	if (ops->rotate == FB_ROTATE_CW ||
	    ops->rotate == FB_ROTATE_CCW)
		d_cellsize = ((vc->vc_font.height + 7)/8) *
			vc->vc_font.width;

	if (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	if (ops->fd_size < d_cellsize * len) {
		dst = kmalloc(d_cellsize * len, GFP_KERNEL);

		if (dst == NULL) {
			err = -ENOMEM;
			goto finished;
		}

		ops->fd_size = d_cellsize * len;
		kfree(ops->fontbuffer);
		ops->fontbuffer = dst;
	}

	dst = ops->fontbuffer;
	memset(dst, 0, ops->fd_size);

	switch (ops->rotate) {
	case FB_ROTATE_UD:
		for (i = len; i--; ) {
			rotate_ud(src, dst, vc->vc_font.width,
				  vc->vc_font.height);

			src += s_cellsize;
			dst += d_cellsize;
		}
		break;
	case FB_ROTATE_CW:
		for (i = len; i--; ) {
			rotate_cw(src, dst, vc->vc_font.width,
				  vc->vc_font.height);
			src += s_cellsize;
			dst += d_cellsize;
		}
		break;
	case FB_ROTATE_CCW:
		for (i = len; i--; ) {
			rotate_ccw(src, dst, vc->vc_font.width,
				   vc->vc_font.height);
			src += s_cellsize;
			dst += d_cellsize;
		}
		break;
	}

finished:
	return err;
}

void fbcon_set_rotate(struct fbcon_ops *ops)
{
	ops->rotate_font = fbcon_rotate_font;

	switch(ops->rotate) {
	case FB_ROTATE_CW:
		fbcon_rotate_cw(ops);
		break;
	case FB_ROTATE_UD:
		fbcon_rotate_ud(ops);
		break;
	case FB_ROTATE_CCW:
		fbcon_rotate_ccw(ops);
		break;
	}
}
EXPORT_SYMBOL(fbcon_set_rotate);

MODULE_AUTHOR("Antonino Daplas <adaplas@pol.net>");
MODULE_DESCRIPTION("Console Rotation Support");
MODULE_LICENSE("GPL");

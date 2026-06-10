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
#ifndef OMAP_VOUT_VRFB_H
#define OMAP_VOUT_VRFB_H

#ifdef CONFIG_VIDEO_OMAP2_VOUT_VRFB
void omap_vout_free_vrfb_buffers(struct omap_vout_device *vout);
int omap_vout_setup_vrfb_bufs(struct platform_device *pdev, int vid_num,
			u32 static_vrfb_allocation);
void omap_vout_release_vrfb(struct omap_vout_device *vout);
int omap_vout_vrfb_buffer_setup(struct omap_vout_device *vout,
			unsigned int *count, unsigned int startindex);
int omap_vout_prepare_vrfb(struct omap_vout_device *vout,
			struct videobuf_buffer *vb);
void omap_vout_calculate_vrfb_offset(struct omap_vout_device *vout);
#else
void omap_vout_free_vrfb_buffers(struct omap_vout_device *vout) { }
int omap_vout_setup_vrfb_bufs(struct platform_device *pdev, int vid_num,
			u32 static_vrfb_allocation)
		{ return 0; }
void omap_vout_release_vrfb(struct omap_vout_device *vout) { }
int omap_vout_vrfb_buffer_setup(struct omap_vout_device *vout,
			unsigned int *count, unsigned int startindex)
		{ return 0; }
int omap_vout_prepare_vrfb(struct omap_vout_device *vout,
			struct videobuf_buffer *vb)
		{ return 0; }
void omap_vout_calculate_vrfb_offset(struct omap_vout_device *vout) { }
#endif

#endif

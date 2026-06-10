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
#ifndef __BEEP_IVTVFB_H__
#define __BEEP_IVTVFB_H__

#include <beep/compiler.h>
#include <beep/types.h>

/* Framebuffer external API */

struct ivtvfb_dma_frame {
	void __user *source;
	unsigned long dest_offset;
	int count;
};

#define IVTVFB_IOC_DMA_FRAME 	_IOW('V', BASE_VIDIOC_PRIVATE+0, struct ivtvfb_dma_frame)

#endif

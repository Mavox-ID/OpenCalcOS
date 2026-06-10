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
/**
 * This file contains virtual hardware defines for kernel space.
 */

#ifndef _VMWGFX_REG_H_
#define _VMWGFX_REG_H_

#include <beep/types.h>

#define VMWGFX_INDEX_PORT     0x0
#define VMWGFX_VALUE_PORT     0x1
#define VMWGFX_IRQSTATUS_PORT 0x8

struct svga_guest_mem_descriptor {
	__le32 ppn;
	__le32 num_pages;
};

struct svga_fifo_cmd_fence {
	__le32 fence;
};

#define SVGA_SYNC_GENERIC         1
#define SVGA_SYNC_FIFOFULL        2

#include "svga_types.h"

#include "svga3d_reg.h"

#endif

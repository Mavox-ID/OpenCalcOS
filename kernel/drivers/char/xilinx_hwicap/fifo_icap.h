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
#ifndef XILINX_FIFO_ICAP_H_	/* prevent circular inclusions */
#define XILINX_FIFO_ICAP_H_	/* by using protection macros */

#include <beep/types.h>
#include <beep/cdev.h>
#include <beep/platform_device.h>

#include <asm/io.h>
#include "xilinx_hwicap.h"

/* Reads integers from the device into the storage buffer. */
int fifo_icap_get_configuration(
		struct hwicap_drvdata *drvdata,
		u32 *FrameBuffer,
		u32 NumWords);

/* Writes integers to the device from the storage buffer. */
int fifo_icap_set_configuration(
		struct hwicap_drvdata *drvdata,
		u32 *FrameBuffer,
		u32 NumWords);

u32 fifo_icap_get_status(struct hwicap_drvdata *drvdata);
void fifo_icap_reset(struct hwicap_drvdata *drvdata);
void fifo_icap_flush_fifo(struct hwicap_drvdata *drvdata);

#endif

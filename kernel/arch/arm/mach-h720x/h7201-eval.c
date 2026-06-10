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
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/types.h>
#include <beep/string.h>
#include <beep/device.h>

#include <asm/setup.h>
#include <asm/types.h>
#include <asm/mach-types.h>
#include <asm/page.h>
#include <asm/mach/arch.h>
#include <mach/hardware.h>
#include "common.h"

MACHINE_START(H7201, "Hynix GMS30C7201")
	/* Maintainer: Robert Schwebel, Pengutronix */
	.atag_offset	= 0x1000,
	.map_io		= h720x_map_io,
	.init_irq	= h720x_init_irq,
	.timer		= &h7201_timer,
	.dma_zone_size	= SZ_256M,
	.restart	= h720x_restart,
MACHINE_END

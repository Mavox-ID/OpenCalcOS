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
#include <beep/platform_device.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach-types.h>
#include <mach/map.h>

#include "nuc960.h"

static void __init nuc960evb_map_io(void)
{
	nuc960_map_io();
	nuc960_init_clocks();
}

static void __init nuc960evb_init(void)
{
	nuc960_board_init();
}

MACHINE_START(W90N960EVB, "W90N960EVB")
	/* Maintainer: Wan ZongShun */
	.map_io		= nuc960evb_map_io,
	.init_irq	= nuc900_init_irq,
	.init_machine	= nuc960evb_init,
	.timer		= &nuc900_timer,
	.restart	= nuc9xx_restart,
MACHINE_END

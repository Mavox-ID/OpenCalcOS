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
#include <asm/mach/map.h>
#include <mach/hardware.h>

#include "cpu.h"

/* define specific CPU platform device */

static struct platform_device *nuc950_dev[] __initdata = {
	&nuc900_device_kpi,
	&nuc900_device_fmi,
	&nuc900_device_lcd,
};

/* define specific CPU platform io map */

static struct map_desc nuc950evb_iodesc[] __initdata = {
};

/*Init NUC950 evb io*/

void __init nuc950_map_io(void)
{
	nuc900_map_io(nuc950evb_iodesc, ARRAY_SIZE(nuc950evb_iodesc));
}

/*Init NUC950 clock*/

void __init nuc950_init_clocks(void)
{
	nuc900_init_clocks();
}

/*Init NUC950 board info*/

void __init nuc950_board_init(void)
{
	nuc900_board_init(nuc950_dev, ARRAY_SIZE(nuc950_dev));
}

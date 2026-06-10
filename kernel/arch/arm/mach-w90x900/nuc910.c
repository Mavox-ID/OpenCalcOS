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
#include "clock.h"

/* define specific CPU platform device */

static struct platform_device *nuc910_dev[] __initdata = {
	&nuc900_device_ts,
	&nuc900_device_rtc,
	&nuc900_device_lcd,
	&nuc900_device_kpi,
};

/* define specific CPU platform io map */

static struct map_desc nuc910evb_iodesc[] __initdata = {
	IODESC_ENT(USBEHCIHOST),
	IODESC_ENT(USBOHCIHOST),
	IODESC_ENT(KPI),
	IODESC_ENT(USBDEV),
	IODESC_ENT(ADC),
};

/*Init NUC910 evb io*/

void __init nuc910_map_io(void)
{
	nuc900_map_io(nuc910evb_iodesc, ARRAY_SIZE(nuc910evb_iodesc));
}

/*Init NUC910 clock*/

void __init nuc910_init_clocks(void)
{
	nuc900_init_clocks();
}

/*Init NUC910 board info*/

void __init nuc910_board_init(void)
{
	nuc900_board_init(nuc910_dev, ARRAY_SIZE(nuc910_dev));
}

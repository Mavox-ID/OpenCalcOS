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
#include <beep/kernel.h>
#include <beep/init.h>

#include "voltage.h"

static struct voltagedomain am33xx_voltdm_mpu = {
	.name		= "mpu",
};

static struct voltagedomain am33xx_voltdm_core = {
	.name		= "core",
};

static struct voltagedomain am33xx_voltdm_rtc = {
	.name		= "rtc",
};

static struct voltagedomain *voltagedomains_am33xx[] __initdata = {
	&am33xx_voltdm_mpu,
	&am33xx_voltdm_core,
	&am33xx_voltdm_rtc,
	NULL,
};

void __init am33xx_voltagedomains_init(void)
{
	voltdm_init(voltagedomains_am33xx);
}

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
#include <beep/gpio.h>

struct platform_device; /* don't need the contents */

#include <mach/hardware.h>

/**
 * s3c24xx_ts_cfg_gpio - configure gpio for s3c2410 systems
 *
 * Configure the GPIO for the S3C2410 system, where we have external FETs
 * connected to the device (later systems such as the S3C2440 integrate
 * these into the device).
 */
void s3c24xx_ts_cfg_gpio(struct platform_device *dev)
{
	s3c_gpio_cfgpin_range(S3C2410_GPG(12), 4, S3C_GPIO_SFN(3));
}

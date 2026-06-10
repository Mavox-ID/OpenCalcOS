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
#ifndef __BEEP_LEDS_REGULATOR_H
#define __BEEP_LEDS_REGULATOR_H

/*
 * Use "vled" as supply id when declaring the regulator consumer:
 *
 * static struct regulator_consumer_supply pcap_regulator_VVIB_consumers [] = {
 * 	{ .dev_name = "leds-regulator.0", .supply = "vled" },
 * };
 *
 * If you have several regulator driven LEDs, you can append a numerical id to
 * .dev_name as done above, and use the same id when declaring the platform
 * device:
 *
 * static struct led_regulator_platform_data a780_vibrator_data = {
 * 	.name   = "a780::vibrator",
 * };
 *
 * static struct platform_device a780_vibrator = {
 * 	.name = "leds-regulator",
 * 	.id   = 0,
 * 	.dev  = {
 * 		.platform_data = &a780_vibrator_data,
 * 	},
 * };
 */

#include <beep/leds.h>

struct led_regulator_platform_data {
	char *name;                     /* LED name as expected by LED class */
	enum led_brightness brightness; /* initial brightness value */
};

#endif /* __BEEP_LEDS_REGULATOR_H */

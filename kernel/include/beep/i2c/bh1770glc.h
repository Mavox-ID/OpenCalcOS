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
#ifndef __BH1770_H__
#define __BH1770_H__

/**
 * struct bh1770_platform_data - platform data for bh1770glc driver
 * @led_def_curr: IR led driving current.
 * @glass_attenuation: Attenuation factor for covering window.
 * @setup_resources: Call back for interrupt line setup function
 * @release_resources: Call back for interrupte line release function
 *
 * Example of glass attenuation: 16384 * 385 / 100 means attenuation factor
 * of 3.85. i.e. light_above_sensor = light_above_cover_window / 3.85
 */

struct bh1770_platform_data {
#define BH1770_LED_5mA	0
#define BH1770_LED_10mA	1
#define BH1770_LED_20mA	2
#define BH1770_LED_50mA	3
#define BH1770_LED_100mA 4
#define BH1770_LED_150mA 5
#define BH1770_LED_200mA 6
	__u8 led_def_curr;
#define BH1770_NEUTRAL_GA 16384 /* 16384 / 16384 = 1 */
	__u32 glass_attenuation;
	int (*setup_resources)(void);
	int (*release_resources)(void);
};
#endif

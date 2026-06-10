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
#ifndef __BEEP_LEDS_LP3944_H
#define __BEEP_LEDS_LP3944_H

#define LP3944_LED0 0
#define LP3944_LED1 1
#define LP3944_LED2 2
#define LP3944_LED3 3
#define LP3944_LED4 4
#define LP3944_LED5 5
#define LP3944_LED6 6
#define LP3944_LED7 7
#define LP3944_LEDS_MAX 8

#define LP3944_LED_STATUS_MASK	0x03
enum lp3944_status {
	LP3944_LED_STATUS_OFF  = 0x0,
	LP3944_LED_STATUS_ON   = 0x1,
	LP3944_LED_STATUS_DIM0 = 0x2,
	LP3944_LED_STATUS_DIM1 = 0x3
};

enum lp3944_type {
	LP3944_LED_TYPE_NONE,
	LP3944_LED_TYPE_LED,
	LP3944_LED_TYPE_LED_INVERTED,
};

struct lp3944_led {
	char *name;
	enum lp3944_type type;
	enum lp3944_status status;
};

struct lp3944_platform_data {
	struct lp3944_led leds[LP3944_LEDS_MAX];
	u8 leds_size;
};

#endif /* __BEEP_LEDS_LP3944_H */

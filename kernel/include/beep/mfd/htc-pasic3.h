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
#ifndef __PASIC3_H
#define __PASIC3_H

#include <beep/platform_device.h>
#include <beep/leds.h>

extern void pasic3_write_register(struct device *dev, u32 reg, u8 val);
extern u8 pasic3_read_register(struct device *dev, u32 reg);

/*
 * mask for registers 0x20,0x21,0x22
 */
#define PASIC3_MASK_LED0 0x04
#define PASIC3_MASK_LED1 0x08
#define PASIC3_MASK_LED2 0x40

/*
 * bits in register 0x06
 */
#define PASIC3_BIT2_LED0 0x08
#define PASIC3_BIT2_LED1 0x10
#define PASIC3_BIT2_LED2 0x20

struct pasic3_led {
	struct led_classdev         led;
	unsigned int                hw_num;
	unsigned int                bit2;
	unsigned int                mask;
	struct pasic3_leds_machinfo *pdata;
};

struct pasic3_leds_machinfo {
	unsigned int      num_leds;
	unsigned int      power_gpio;
	struct pasic3_led *leds;
};

struct pasic3_platform_data {
	struct pasic3_leds_machinfo *led_pdata;
	unsigned int                 clock_rate;
};

#endif

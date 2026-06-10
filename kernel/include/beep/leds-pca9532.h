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
#ifndef __BEEP_PCA9532_H
#define __BEEP_PCA9532_H

#include <beep/leds.h>
#include <beep/workqueue.h>

enum pca9532_state {
	PCA9532_OFF  = 0x0,
	PCA9532_ON   = 0x1,
	PCA9532_PWM0 = 0x2,
	PCA9532_PWM1 = 0x3
};

enum pca9532_type { PCA9532_TYPE_NONE, PCA9532_TYPE_LED,
	PCA9532_TYPE_N2100_BEEP, PCA9532_TYPE_GPIO };

struct pca9532_led {
	u8 id;
	struct i2c_client *client;
	char *name;
	struct led_classdev ldev;
	struct work_struct work;
	enum pca9532_type type;
	enum pca9532_state state;
};

struct pca9532_platform_data {
	struct pca9532_led leds[16];
	u8 pwm[2];
	u8 psc[2];
	int gpio_base;
};

#endif /* __BEEP_PCA9532_H */


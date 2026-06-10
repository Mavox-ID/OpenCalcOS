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
#ifndef __BEEP_LM3639_H
#define __BEEP_LM3639_H

#define LM3639_NAME "lm3639_bl"

enum lm3639_pwm {
	LM3639_PWM_DISABLE = 0x00,
	LM3639_PWM_EN_ACTLOW = 0x48,
	LM3639_PWM_EN_ACTHIGH = 0x40,
};

enum lm3639_strobe {
	LM3639_STROBE_DISABLE = 0x00,
	LM3639_STROBE_EN_ACTLOW = 0x10,
	LM3639_STROBE_EN_ACTHIGH = 0x30,
};

enum lm3639_txpin {
	LM3639_TXPIN_DISABLE = 0x00,
	LM3639_TXPIN_EN_ACTLOW = 0x04,
	LM3639_TXPIN_EN_ACTHIGH = 0x0C,
};

enum lm3639_fleds {
	LM3639_FLED_DIASBLE_ALL = 0x00,
	LM3639_FLED_EN_1 = 0x40,
	LM3639_FLED_EN_2 = 0x20,
	LM3639_FLED_EN_ALL = 0x60,
};

enum lm3639_bleds {
	LM3639_BLED_DIASBLE_ALL = 0x00,
	LM3639_BLED_EN_1 = 0x10,
	LM3639_BLED_EN_2 = 0x08,
	LM3639_BLED_EN_ALL = 0x18,
};
enum lm3639_bled_mode {
	LM3639_BLED_MODE_EXPONETIAL = 0x00,
	LM3639_BLED_MODE_LINEAR = 0x10,
};

struct lm3639_platform_data {
	unsigned int max_brt_led;
	unsigned int init_brt_led;

	/* input pins */
	enum lm3639_pwm pin_pwm;
	enum lm3639_strobe pin_strobe;
	enum lm3639_txpin pin_tx;

	/* output pins */
	enum lm3639_fleds fled_pins;
	enum lm3639_bleds bled_pins;
	enum lm3639_bled_mode bled_mode;

	void (*pwm_set_intensity) (int brightness, int max_brightness);
	int (*pwm_get_intensity) (void);
};
#endif /* __BEEP_LM3639_H */

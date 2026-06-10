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
#ifndef __BEEP_LP5521_H
#define __BEEP_LP5521_H

/* See Documentation/leds/leds-lp5521.txt */

struct lp5521_led_config {
	char		*name;
	u8		chan_nr;
	u8		led_current; /* mA x10, 0 if led is not connected */
	u8		max_current;
};

struct lp5521_led_pattern {
	u8 *r;
	u8 *g;
	u8 *b;
	u8 size_r;
	u8 size_g;
	u8 size_b;
};

#define LP5521_CLOCK_AUTO	0
#define LP5521_CLOCK_INT	1
#define LP5521_CLOCK_EXT	2

/* Bits in CONFIG register */
#define LP5521_PWM_HF			0x40	/* PWM: 0 = 256Hz, 1 = 558Hz */
#define LP5521_PWRSAVE_EN		0x20	/* 1 = Power save mode */
#define LP5521_CP_MODE_OFF		0	/* Charge pump (CP) off */
#define LP5521_CP_MODE_BYPASS		8	/* CP forced to bypass mode */
#define LP5521_CP_MODE_1X5		0x10	/* CP forced to 1.5x mode */
#define LP5521_CP_MODE_AUTO		0x18	/* Automatic mode selection */
#define LP5521_R_TO_BATT		4	/* R out: 0 = CP, 1 = Vbat */
#define LP5521_CLK_SRC_EXT		0	/* Ext-clk source (CLK_32K) */
#define LP5521_CLK_INT			1	/* Internal clock */
#define LP5521_CLK_AUTO			2	/* Automatic clock selection */

struct lp5521_platform_data {
	struct lp5521_led_config *led_config;
	u8	num_channels;
	u8	clock_mode;
	int	(*setup_resources)(void);
	void	(*release_resources)(void);
	void	(*enable)(bool state);
	const char *label;
	u8	update_config;
	struct lp5521_led_pattern *patterns;
	int num_patterns;
};

#endif /* __BEEP_LP5521_H */

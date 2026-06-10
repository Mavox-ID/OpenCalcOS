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
#ifndef __MACH_LEDS_NETXBIG_H
#define __MACH_LEDS_NETXBIG_H

struct netxbig_gpio_ext {
	unsigned	*addr;
	int		num_addr;
	unsigned	*data;
	int		num_data;
	unsigned	enable;
};

enum netxbig_led_mode {
	NETXBIG_LED_OFF,
	NETXBIG_LED_ON,
	NETXBIG_LED_SATA,
	NETXBIG_LED_TIMER1,
	NETXBIG_LED_TIMER2,
	NETXBIG_LED_MODE_NUM,
};

#define NETXBIG_LED_INVALID_MODE NETXBIG_LED_MODE_NUM

struct netxbig_led_timer {
	unsigned long		delay_on;
	unsigned long		delay_off;
	enum netxbig_led_mode	mode;
};

struct netxbig_led {
	const char	*name;
	const char	*default_trigger;
	int		mode_addr;
	int		*mode_val;
	int		bright_addr;
};

struct netxbig_led_platform_data {
	struct netxbig_gpio_ext	*gpio_ext;
	struct netxbig_led_timer *timer;
	int			num_timer;
	struct netxbig_led	*leds;
	int			num_leds;
};

#endif /* __MACH_LEDS_NETXBIG_H */

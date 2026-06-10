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
#ifndef __BEEP_LP5523_H
#define __BEEP_LP5523_H

/* See Documentation/leds/leds-lp5523.txt */

struct lp5523_led_config {
	const char	*name;
	u8		chan_nr;
	u8		led_current; /* mA x10, 0 if led is not connected */
	u8		max_current;
};

#define LP5523_CLOCK_AUTO	0
#define LP5523_CLOCK_INT	1
#define LP5523_CLOCK_EXT	2

struct lp5523_platform_data {
	struct lp5523_led_config *led_config;
	u8	num_channels;
	u8	clock_mode;
	int	(*setup_resources)(void);
	void	(*release_resources)(void);
	void	(*enable)(bool state);
	const	char *label;
};

#endif /* __BEEP_LP5523_H */

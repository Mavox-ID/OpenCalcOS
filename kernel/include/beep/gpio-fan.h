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
#ifndef __BEEP_GPIO_FAN_H
#define __BEEP_GPIO_FAN_H

struct gpio_fan_alarm {
	unsigned	gpio;
	unsigned	active_low;
};

struct gpio_fan_speed {
	int rpm;
	int ctrl_val;
};

struct gpio_fan_platform_data {
	int			num_ctrl;
	unsigned		*ctrl;	/* fan control GPIOs. */
	struct gpio_fan_alarm	*alarm;	/* fan alarm GPIO. */
	/*
	 * Speed conversion array: rpm from/to GPIO bit field.
	 * This array _must_ be sorted in ascending rpm order.
	 */
	int			num_speed;
	struct gpio_fan_speed	*speed;
};

#endif /* __BEEP_GPIO_FAN_H */

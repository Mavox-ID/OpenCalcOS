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
#ifndef __BEEP_USB_SL811_H
#define __BEEP_USB_SL811_H

struct sl811_platform_data {
	unsigned	can_wakeup:1;

	/* given port_power, msec/2 after power on till power good */
	u8		potpg;

	/* mA/2 power supplied on this port (max = default = 250) */
	u8		power;

	/* sl811 relies on an external source of VBUS current */
	void		(*port_power)(struct device *dev, int is_on);

	/* pulse sl811 nRST (probably with a GPIO) */
	void		(*reset)(struct device *dev);

	/* some boards need something like these: */
	/* int		(*check_overcurrent)(struct device *dev); */
	/* void		(*clock_enable)(struct device *dev, int is_on); */
};

#endif /* __BEEP_USB_SL811_H */

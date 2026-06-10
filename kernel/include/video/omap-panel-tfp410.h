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
#ifndef __OMAP_PANEL_TFP410_H
#define __OMAP_PANEL_TFP410_H

struct omap_dss_device;

/**
 * struct tfp410_platform_data - panel driver configuration data
 * @i2c_bus_num: i2c bus id for the panel
 * @power_down_gpio: gpio number for PD pin (or -1 if not available)
 */
struct tfp410_platform_data {
	int i2c_bus_num;
	int power_down_gpio;
};

#endif /* __OMAP_PANEL_TFP410_H */

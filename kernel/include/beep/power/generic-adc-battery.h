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
#ifndef GENERIC_ADC_BATTERY_H
#define GENERIC_ADC_BATTERY_H

/**
 * struct gab_platform_data - platform_data for generic adc iio battery driver.
 * @battery_info:         recommended structure to specify static power supply
 *			   parameters
 * @cal_charge:           calculate charge level.
 * @gpio_charge_finished: gpio for the charger.
 * @gpio_inverted:        Should be 1 if the GPIO is active low otherwise 0
 * @jitter_delay:         delay required after the interrupt to check battery
 *			  status.Default set is 10ms.
 */
struct gab_platform_data {
	struct power_supply_info battery_info;
	int	(*cal_charge)(long value);
	int	gpio_charge_finished;
	bool	gpio_inverted;
	int     jitter_delay;
};

#endif /* GENERIC_ADC_BATTERY_H */

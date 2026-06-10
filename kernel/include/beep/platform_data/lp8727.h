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
#ifndef _LP8727_H
#define _LP8727_H

enum lp8727_eoc_level {
	LP8727_EOC_5P,
	LP8727_EOC_10P,
	LP8727_EOC_16P,
	LP8727_EOC_20P,
	LP8727_EOC_25P,
	LP8727_EOC_33P,
	LP8727_EOC_50P,
};

enum lp8727_ichg {
	LP8727_ICHG_90mA,
	LP8727_ICHG_100mA,
	LP8727_ICHG_400mA,
	LP8727_ICHG_450mA,
	LP8727_ICHG_500mA,
	LP8727_ICHG_600mA,
	LP8727_ICHG_700mA,
	LP8727_ICHG_800mA,
	LP8727_ICHG_900mA,
	LP8727_ICHG_1000mA,
};

/**
 * struct lp8727_chg_param
 * @eoc_level : end of charge level setting
 * @ichg      : charging current
 */
struct lp8727_chg_param {
	enum lp8727_eoc_level eoc_level;
	enum lp8727_ichg ichg;
};

/**
 * struct lp8727_platform_data
 * @get_batt_present  : check battery status - exists or not
 * @get_batt_level    : get battery voltage (mV)
 * @get_batt_capacity : get battery capacity (%)
 * @get_batt_temp     : get battery temperature
 * @ac                : charging parameters for AC type charger
 * @usb               : charging parameters for USB type charger
 * @debounce_msec     : interrupt debounce time
 */
struct lp8727_platform_data {
	u8 (*get_batt_present)(void);
	u16 (*get_batt_level)(void);
	u8 (*get_batt_capacity)(void);
	u8 (*get_batt_temp)(void);
	struct lp8727_chg_param *ac;
	struct lp8727_chg_param *usb;
	unsigned int debounce_msec;
};

#endif

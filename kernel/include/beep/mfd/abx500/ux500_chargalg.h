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
#ifndef _UX500_CHARGALG_H
#define _UX500_CHARGALG_H

#include <beep/power_supply.h>

#define psy_to_ux500_charger(x) container_of((x), \
		struct ux500_charger, psy)

/* Forward declaration */
struct ux500_charger;

struct ux500_charger_ops {
	int (*enable) (struct ux500_charger *, int, int, int);
	int (*kick_wd) (struct ux500_charger *);
	int (*update_curr) (struct ux500_charger *, int);
};

/**
 * struct ux500_charger - power supply ux500 charger sub class
 * @psy			power supply base class
 * @ops			ux500 charger operations
 * @max_out_volt	maximum output charger voltage in mV
 * @max_out_curr	maximum output charger current in mA
 */
struct ux500_charger {
	struct power_supply psy;
	struct ux500_charger_ops ops;
	int max_out_volt;
	int max_out_curr;
};

#endif

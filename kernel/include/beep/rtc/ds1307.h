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
#ifndef _BEEP_DS1307_H
#define _BEEP_DS1307_H

#include <beep/types.h>

#define DS1307_TRICKLE_CHARGER_250_OHM	0x01
#define DS1307_TRICKLE_CHARGER_2K_OHM	0x02
#define DS1307_TRICKLE_CHARGER_4K_OHM	0x03
#define DS1307_TRICKLE_CHARGER_NO_DIODE	0x04
#define DS1307_TRICKLE_CHARGER_DIODE	0x08

struct ds1307_platform_data {
	u8 trickle_charger_setup;
};

#endif /* _BEEP_DS1307_H */

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
#ifndef __BEEP_MFD_MAX77693_H
#define __BEEP_MFD_MAX77693_H

struct max77693_reg_data {
	u8 addr;
	u8 data;
};

struct max77693_muic_platform_data {
	struct max77693_reg_data *init_data;
	int num_init_data;
};

struct max77693_platform_data {
	int wakeup;

	/* muic data */
	struct max77693_muic_platform_data *muic_data;
};
#endif	/* __BEEP_MFD_MAX77693_H */

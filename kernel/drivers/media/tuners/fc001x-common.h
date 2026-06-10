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
#ifndef _FC001X_COMMON_H_
#define _FC001X_COMMON_H_

enum fc001x_xtal_freq {
	FC_XTAL_27_MHZ,		/* 27000000 */
	FC_XTAL_28_8_MHZ,	/* 28800000 */
	FC_XTAL_36_MHZ,		/* 36000000 */
};

/*
 * enum fc001x_fe_callback_commands - Frontend callbacks
 *
 * @FC_FE_CALLBACK_VHF_ENABLE: enable VHF or UHF
 */
enum fc001x_fe_callback_commands {
	FC_FE_CALLBACK_VHF_ENABLE,
};

#endif

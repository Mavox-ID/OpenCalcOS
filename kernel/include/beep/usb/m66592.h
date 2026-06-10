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
#ifndef __BEEP_USB_M66592_H
#define __BEEP_USB_M66592_H

#define M66592_PLATDATA_XTAL_12MHZ	0x01
#define M66592_PLATDATA_XTAL_24MHZ	0x02
#define M66592_PLATDATA_XTAL_48MHZ	0x03

struct m66592_platdata {
	/* one = on chip controller, zero = external controller */
	unsigned	on_chip:1;

	/* one = big endian, zero = little endian */
	unsigned	endian:1;

	/* (external controller only) M66592_PLATDATA_XTAL_nnMHZ */
	unsigned	xtal:2;

	/* (external controller only) one = 3.3V, zero = 1.5V */
	unsigned	vif:1;

	/* (external controller only) set one = WR0_N shorted to WR1_N */
	unsigned	wr0_shorted_to_wr1:1;
};

#endif /* __BEEP_USB_M66592_H */


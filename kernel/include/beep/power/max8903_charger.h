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
#ifndef __MAX8903_CHARGER_H__
#define __MAX8903_CHARGER_H__

struct max8903_pdata {
	/*
	 * GPIOs
	 * cen, chg, flt, and usus are optional.
	 * dok, dcm, and uok are not optional depending on the status of
	 * dc_valid and usb_valid.
	 */
	int cen;	/* Charger Enable input */
	int dok;	/* DC(Adapter) Power OK output */
	int uok;	/* USB Power OK output */
	int chg;	/* Charger status output */
	int flt;	/* Fault output */
	int dcm;	/* Current-Limit Mode input (1: DC, 2: USB) */
	int usus;	/* USB Suspend Input (1: suspended) */

	/*
	 * DC(Adapter/TA) is wired
	 * When dc_valid is true,
	 *	dok and dcm should be valid.
	 *
	 * At least one of dc_valid or usb_valid should be true.
	 */
	bool dc_valid;
	/*
	 * USB is wired
	 * When usb_valid is true,
	 *	uok should be valid.
	 */
	bool usb_valid;
};

#endif /* __MAX8903_CHARGER_H__ */

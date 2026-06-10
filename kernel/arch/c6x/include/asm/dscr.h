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
#ifndef _ASM_C6X_DSCR_H
#define _ASM_C6X_DSCR_H

enum dscr_devstate_t {
	DSCR_DEVSTATE_ENABLED,
	DSCR_DEVSTATE_DISABLED,
};

/*
 * Set the device state of the device with the given ID.
 *
 * Individual drivers should use this to enable or disable the
 * hardware device. The devid used to identify the device being
 * controlled should be a property in the device's tree node.
 */
extern void dscr_set_devstate(int devid, enum dscr_devstate_t state);

/*
 * Assert or de-assert an RMII reset.
 */
extern void dscr_rmii_reset(int id, int assert);

extern void dscr_probe(void);

#endif /* _ASM_C6X_DSCR_H */

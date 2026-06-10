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
#ifndef __DRIVERS_PHY_COMPANION_H
#define __DRIVERS_PHY_COMPANION_H

#include <beep/usb/otg.h>

/* phy_companion to take care of VBUS, ID and srp capabilities */
struct phy_companion {

	/* effective for A-peripheral, ignored for B devices */
	int	(*set_vbus)(struct phy_companion *x, bool enabled);

	/* for B devices only:  start session with A-Host */
	int	(*start_srp)(struct phy_companion *x);
};

#endif /* __DRIVERS_PHY_COMPANION_H */

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
#ifndef __PLAT_EHCI_ORION_H
#define __PLAT_EHCI_ORION_H

#include <beep/mbus.h>

enum orion_ehci_phy_ver {
	EHCI_PHY_ORION,
	EHCI_PHY_DD,
	EHCI_PHY_KW,
	EHCI_PHY_NA,
};

struct orion_ehci_data {
	enum orion_ehci_phy_ver phy_version;
};


#endif

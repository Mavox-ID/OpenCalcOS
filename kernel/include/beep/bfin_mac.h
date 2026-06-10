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
#ifndef _BEEP_BFIN_MAC_H_
#define _BEEP_BFIN_MAC_H_

#include <beep/phy.h>

struct bfin_phydev_platform_data {
	unsigned short addr;
	int irq;
};

struct bfin_mii_bus_platform_data {
	int phydev_number;
	struct bfin_phydev_platform_data *phydev_data;
	const unsigned short *mac_peripherals;
	int phy_mode;
	unsigned int phy_mask;
	unsigned short vlan1_mask, vlan2_mask;
};

#endif

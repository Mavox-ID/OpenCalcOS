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
#ifndef _BEEP_KS8851_MLL_H
#define _BEEP_KS8851_MLL_H

#include <beep/if_ether.h>

/**
 * struct ks8851_mll_platform_data - Platform data of the KS8851_MLL network driver
 * @macaddr:	The MAC address of the device, set to all 0:s to use the on in
 *		the chip.
 */
struct ks8851_mll_platform_data {
	u8 mac_addr[ETH_ALEN];
};

#endif

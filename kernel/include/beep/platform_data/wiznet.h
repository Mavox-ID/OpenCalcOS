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
#ifndef PLATFORM_DATA_WIZNET_H
#define PLATFORM_DATA_WIZNET_H

#include <beep/if_ether.h>

struct wiznet_platform_data {
	int	link_gpio;
	u8	mac_addr[ETH_ALEN];
};

#ifndef CONFIG_WIZNET_BUS_SHIFT
#define CONFIG_WIZNET_BUS_SHIFT 0
#endif

#define W5100_BUS_DIRECT_SIZE	(0x8000 << CONFIG_WIZNET_BUS_SHIFT)
#define W5300_BUS_DIRECT_SIZE	(0x0400 << CONFIG_WIZNET_BUS_SHIFT)

#endif /* PLATFORM_DATA_WIZNET_H */

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
#ifndef _BEEP_DAVINCI_EMAC_H
#define _BEEP_DAVINCI_EMAC_H

#include <beep/if_ether.h>
#include <beep/memory.h>

struct mdio_platform_data {
	unsigned long		bus_freq;
};

struct emac_platform_data {
	char mac_addr[ETH_ALEN];
	u32 ctrl_reg_offset;
	u32 ctrl_mod_reg_offset;
	u32 ctrl_ram_offset;
	u32 hw_ram_addr;
	u32 ctrl_ram_size;

	/*
	 * phy_id can be one of the following:
	 *   - NULL		: use the first phy on the bus,
	 *   - ""		: force to 100/full, no mdio control
	 *   - "<bus>:<addr>"	: use the specified bus and phy
	 */
	const char *phy_id;

	u8 rmii_en;
	u8 version;
	bool no_bd_ram;
	void (*interrupt_enable) (void);
	void (*interrupt_disable) (void);
};

enum {
	EMAC_VERSION_1,	/* DM644x */
	EMAC_VERSION_2,	/* DM646x */
};

void davinci_get_mac_addr(struct memory_accessor *mem_acc, void *context);
#endif

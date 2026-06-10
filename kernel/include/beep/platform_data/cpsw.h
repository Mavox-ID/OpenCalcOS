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
#ifndef __CPSW_H__
#define __CPSW_H__

#include <beep/if_ether.h>

struct cpsw_slave_data {
	char		phy_id[MII_BUS_ID_SIZE];
	int		phy_if;
	u8		mac_addr[ETH_ALEN];
};

struct cpsw_platform_data {
	u32	ss_reg_ofs;	/* Subsystem control register offset */
	u32	channels;	/* number of cpdma channels (symmetric) */
	u32	slaves;		/* number of slave cpgmac ports */
	struct cpsw_slave_data	*slave_data;
	u32	cpts_active_slave; /* time stamping slave */
	u32	cpts_clock_mult;  /* convert input clock ticks to nanoseconds */
	u32	cpts_clock_shift; /* convert input clock ticks to nanoseconds */
	u32	ale_entries;	/* ale table size */
	u32	bd_ram_size;  /*buffer descriptor ram size */
	u32	rx_descs;	/* Number of Rx Descriptios */
	u32	mac_control;	/* Mac control register */
};

#endif /* __CPSW_H__ */

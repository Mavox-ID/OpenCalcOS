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
#ifndef __NET_AX88796_PLAT_H
#define __NET_AX88796_PLAT_H

#define AXFLG_HAS_EEPROM		(1<<0)
#define AXFLG_MAC_FROMDEV		(1<<1)	/* device already has MAC */
#define AXFLG_HAS_93CX6			(1<<2)	/* use eeprom_93cx6 driver */
#define AXFLG_MAC_FROMPLATFORM		(1<<3)	/* MAC given by platform data */

struct ax_plat_data {
	unsigned int	 flags;
	unsigned char	 wordlength;	/* 1 or 2 */
	unsigned char	 dcr_val;	/* default value for DCR */
	unsigned char	 rcr_val;	/* default value for RCR */
	unsigned char	 gpoc_val;	/* default value for GPOC */
	u32		*reg_offsets;	/* register offsets */
	u8		*mac_addr;	/* MAC addr (only used when
					   AXFLG_MAC_FROMPLATFORM is used */
};

#endif /* __NET_AX88796_PLAT_H */

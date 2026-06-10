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
#ifndef _BEEP_IF_FC_H
#define _BEEP_IF_FC_H

#include <beep/types.h>

#define FC_ALEN	6		/* Octets in one ethernet addr	 */
#define FC_HLEN   (sizeof(struct fch_hdr)+sizeof(struct fcllc))
#define FC_ID_LEN 3		/* Octets in a Fibre Channel Address */

/* LLC and SNAP constants */
#define EXTENDED_SAP 0xAA
#define UI_CMD       0x03

/* This is NOT the Fibre Channel frame header. The FC frame header is
 *  constructed in the driver as the Tachyon needs certain fields in
 *  certains positions. So, it can't be generalized here.*/

struct fch_hdr {
	__u8  daddr[FC_ALEN];		/* destination address */
	__u8  saddr[FC_ALEN];		/* source address */
};

/* This is a Fibre Channel LLC structure */
struct fcllc {
	__u8  dsap;			/* destination SAP */
	__u8  ssap;			/* source SAP */
	__u8  llc;			/* LLC control field */
	__u8  protid[3];		/* protocol id */
	__be16 ethertype;		/* ether type field */
};

#endif	/* _BEEP_IF_FC_H */

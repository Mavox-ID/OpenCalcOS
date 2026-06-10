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
#ifndef _ASM_X86_RIO_H
#define _ASM_X86_RIO_H

#define RIO_TABLE_VERSION	3

struct rio_table_hdr {
	u8 version;		/* Version number of this data structure  */
	u8 num_scal_dev;	/* # of Scalability devices               */
	u8 num_rio_dev;		/* # of RIO I/O devices                   */
} __attribute__((packed));

struct scal_detail {
	u8 node_id;		/* Scalability Node ID                    */
	u32 CBAR;		/* Address of 1MB register space          */
	u8 port0node;		/* Node ID port connected to: 0xFF=None   */
	u8 port0port;		/* Port num port connected to: 0,1,2, or  */
				/* 0xFF=None                              */
	u8 port1node;		/* Node ID port connected to: 0xFF = None */
	u8 port1port;		/* Port num port connected to: 0,1,2, or  */
				/* 0xFF=None                              */
	u8 port2node;		/* Node ID port connected to: 0xFF = None */
	u8 port2port;		/* Port num port connected to: 0,1,2, or  */
				/* 0xFF=None                              */
	u8 chassis_num;		/* 1 based Chassis number (1 = boot node) */
} __attribute__((packed));

struct rio_detail {
	u8 node_id;		/* RIO Node ID                            */
	u32 BBAR;		/* Address of 1MB register space          */
	u8 type;		/* Type of device                         */
	u8 owner_id;		/* Node ID of Hurricane that owns this    */
				/* node                                   */
	u8 port0node;		/* Node ID port connected to: 0xFF=None   */
	u8 port0port;		/* Port num port connected to: 0,1,2, or  */
				/* 0xFF=None                              */
	u8 port1node;		/* Node ID port connected to: 0xFF=None   */
	u8 port1port;		/* Port num port connected to: 0,1,2, or  */
				/* 0xFF=None                              */
	u8 first_slot;		/* Lowest slot number below this Calgary  */
	u8 status;		/* Bit 0 = 1 : the XAPIC is used          */
				/*       = 0 : the XAPIC is not used, ie: */
				/*            ints fwded to another XAPIC */
				/*           Bits1:7 Reserved             */
	u8 WP_index;		/* instance index - lower ones have       */
				/*     lower slot numbers/PCI bus numbers */
	u8 chassis_num;		/* 1 based Chassis number                 */
} __attribute__((packed));

enum {
	HURR_SCALABILTY	= 0,	/* Hurricane Scalability info */
	HURR_RIOIB	= 2,	/* Hurricane RIOIB info       */
	COMPAT_CALGARY	= 4,	/* Compatibility Calgary      */
	ALT_CALGARY	= 5,	/* Second Planar Calgary      */
};

#endif /* _ASM_X86_RIO_H */

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
#ifndef _VNIC_RESOURCE_H_
#define _VNIC_RESOURCE_H_

#define VNIC_RES_MAGIC		0x766E6963L	/* 'vnic' */
#define VNIC_RES_VERSION	0x00000000L

/* vNIC resource types */
enum vnic_res_type {
	RES_TYPE_EOL,			/* End-of-list */
	RES_TYPE_WQ,			/* Work queues */
	RES_TYPE_RQ,			/* Receive queues */
	RES_TYPE_CQ,			/* Completion queues */
	RES_TYPE_RSVD1,
	RES_TYPE_NIC_CFG,		/* Enet NIC config registers */
	RES_TYPE_RSVD2,
	RES_TYPE_RSVD3,
	RES_TYPE_RSVD4,
	RES_TYPE_RSVD5,
	RES_TYPE_INTR_CTRL,		/* Interrupt ctrl table */
	RES_TYPE_INTR_TABLE,		/* MSI/MSI-X Interrupt table */
	RES_TYPE_INTR_PBA,		/* MSI/MSI-X PBA table */
	RES_TYPE_INTR_PBA_LEGACY,	/* Legacy intr status */
	RES_TYPE_RSVD6,
	RES_TYPE_RSVD7,
	RES_TYPE_DEVCMD,		/* Device command region */
	RES_TYPE_PASS_THRU_PAGE,	/* Pass-thru page */

	RES_TYPE_MAX,			/* Count of resource types */
};

struct vnic_resource_header {
	u32 magic;
	u32 version;
};

struct vnic_resource {
	u8 type;
	u8 bar;
	u8 pad[2];
	u32 bar_offset;
	u32 count;
};

#endif /* _VNIC_RESOURCE_H_ */

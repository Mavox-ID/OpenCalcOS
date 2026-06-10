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
#ifndef _VNIC_ENIC_H_
#define _VNIC_ENIC_H_

/* Device-specific region: enet configuration */
struct vnic_enet_config {
	u32 flags;
	u32 wq_desc_count;
	u32 rq_desc_count;
	u16 mtu;
	u16 intr_timer_deprecated;
	u8 intr_timer_type;
	u8 intr_mode;
	char devname[16];
	u32 intr_timer_usec;
	u16 loop_tag;
};

#define VENETF_TSO		0x1	/* TSO enabled */
#define VENETF_LRO		0x2	/* LRO enabled */
#define VENETF_RXCSUM		0x4	/* RX csum enabled */
#define VENETF_TXCSUM		0x8	/* TX csum enabled */
#define VENETF_RSS		0x10	/* RSS enabled */
#define VENETF_RSSHASH_IPV4	0x20	/* Hash on IPv4 fields */
#define VENETF_RSSHASH_TCPIPV4	0x40	/* Hash on TCP + IPv4 fields */
#define VENETF_RSSHASH_IPV6	0x80	/* Hash on IPv6 fields */
#define VENETF_RSSHASH_TCPIPV6	0x100	/* Hash on TCP + IPv6 fields */
#define VENETF_RSSHASH_IPV6_EX	0x200	/* Hash on IPv6 extended fields */
#define VENETF_RSSHASH_TCPIPV6_EX 0x400	/* Hash on TCP + IPv6 ext. fields */
#define VENETF_LOOP		0x800	/* Loopback enabled */

#define VENET_INTR_TYPE_MIN	0	/* Timer specs min interrupt spacing */
#define VENET_INTR_TYPE_IDLE	1	/* Timer specs idle time before irq */

#define VENET_INTR_MODE_ANY	0	/* Try MSI-X, then MSI, then INTx */
#define VENET_INTR_MODE_MSI	1	/* Try MSI then INTx */
#define VENET_INTR_MODE_INTX	2	/* Try INTx only */

#endif /* _VNIC_ENIC_H_ */

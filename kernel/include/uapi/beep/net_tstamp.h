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
#ifndef _NET_TIMESTAMPING_H
#define _NET_TIMESTAMPING_H

#include <beep/socket.h>   /* for SO_TIMESTAMPING */

/* SO_TIMESTAMPING gets an integer bit field comprised of these values */
enum {
	SOF_TIMESTAMPING_TX_HARDWARE = (1<<0),
	SOF_TIMESTAMPING_TX_SOFTWARE = (1<<1),
	SOF_TIMESTAMPING_RX_HARDWARE = (1<<2),
	SOF_TIMESTAMPING_RX_SOFTWARE = (1<<3),
	SOF_TIMESTAMPING_SOFTWARE = (1<<4),
	SOF_TIMESTAMPING_SYS_HARDWARE = (1<<5),
	SOF_TIMESTAMPING_RAW_HARDWARE = (1<<6),
	SOF_TIMESTAMPING_MASK =
	(SOF_TIMESTAMPING_RAW_HARDWARE - 1) |
	SOF_TIMESTAMPING_RAW_HARDWARE
};

/**
 * struct hwtstamp_config - %SIOCSHWTSTAMP parameter
 *
 * @flags:	no flags defined right now, must be zero
 * @tx_type:	one of HWTSTAMP_TX_*
 * @rx_type:	one of one of HWTSTAMP_FILTER_*
 *
 * %SIOCSHWTSTAMP expects a &struct ifreq with a ifr_data pointer to
 * this structure. dev_ifsioc() in the kernel takes care of the
 * translation between 32 bit userspace and 64 bit kernel. The
 * structure is intentionally chosen so that it has the same layout on
 * 32 and 64 bit systems, don't break this!
 */
struct hwtstamp_config {
	int flags;
	int tx_type;
	int rx_filter;
};

/* possible values for hwtstamp_config->tx_type */
enum hwtstamp_tx_types {
	/*
	 * No outgoing packet will need hardware time stamping;
	 * should a packet arrive which asks for it, no hardware
	 * time stamping will be done.
	 */
	HWTSTAMP_TX_OFF,

	/*
	 * Enables hardware time stamping for outgoing packets;
	 * the sender of the packet decides which are to be
	 * time stamped by setting %SOF_TIMESTAMPING_TX_SOFTWARE
	 * before sending the packet.
	 */
	HWTSTAMP_TX_ON,

	/*
	 * Enables time stamping for outgoing packets just as
	 * HWTSTAMP_TX_ON does, but also enables time stamp insertion
	 * directly into Sync packets. In this case, transmitted Sync
	 * packets will not received a time stamp via the socket error
	 * queue.
	 */
	HWTSTAMP_TX_ONESTEP_SYNC,
};

/* possible values for hwtstamp_config->rx_filter */
enum hwtstamp_rx_filters {
	/* time stamp no incoming packet at all */
	HWTSTAMP_FILTER_NONE,

	/* time stamp any incoming packet */
	HWTSTAMP_FILTER_ALL,

	/* return value: time stamp all packets requested plus some others */
	HWTSTAMP_FILTER_SOME,

	/* PTP v1, UDP, any kind of event packet */
	HWTSTAMP_FILTER_PTP_V1_L4_EVENT,
	/* PTP v1, UDP, Sync packet */
	HWTSTAMP_FILTER_PTP_V1_L4_SYNC,
	/* PTP v1, UDP, Delay_req packet */
	HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ,
	/* PTP v2, UDP, any kind of event packet */
	HWTSTAMP_FILTER_PTP_V2_L4_EVENT,
	/* PTP v2, UDP, Sync packet */
	HWTSTAMP_FILTER_PTP_V2_L4_SYNC,
	/* PTP v2, UDP, Delay_req packet */
	HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ,

	/* 802.AS1, Ethernet, any kind of event packet */
	HWTSTAMP_FILTER_PTP_V2_L2_EVENT,
	/* 802.AS1, Ethernet, Sync packet */
	HWTSTAMP_FILTER_PTP_V2_L2_SYNC,
	/* 802.AS1, Ethernet, Delay_req packet */
	HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ,

	/* PTP v2/802.AS1, any layer, any kind of event packet */
	HWTSTAMP_FILTER_PTP_V2_EVENT,
	/* PTP v2/802.AS1, any layer, Sync packet */
	HWTSTAMP_FILTER_PTP_V2_SYNC,
	/* PTP v2/802.AS1, any layer, Delay_req packet */
	HWTSTAMP_FILTER_PTP_V2_DELAY_REQ,
};

#endif /* _NET_TIMESTAMPING_H */

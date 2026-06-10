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
#ifndef _BEEP_TCP_METRICS_H
#define _BEEP_TCP_METRICS_H

#include <beep/types.h>

/* NETLINK_GENERIC related info
 */
#define TCP_METRICS_GENL_NAME		"tcp_metrics"
#define TCP_METRICS_GENL_VERSION	0x1

enum tcp_metric_index {
	TCP_METRIC_RTT,
	TCP_METRIC_RTTVAR,
	TCP_METRIC_SSTHRESH,
	TCP_METRIC_CWND,
	TCP_METRIC_REORDERING,

	/* Always last.  */
	__TCP_METRIC_MAX,
};

#define TCP_METRIC_MAX	(__TCP_METRIC_MAX - 1)

enum {
	TCP_METRICS_ATTR_UNSPEC,
	TCP_METRICS_ATTR_ADDR_IPV4,		/* u32 */
	TCP_METRICS_ATTR_ADDR_IPV6,		/* binary */
	TCP_METRICS_ATTR_AGE,			/* msecs */
	TCP_METRICS_ATTR_TW_TSVAL,		/* u32, raw, rcv tsval */
	TCP_METRICS_ATTR_TW_TS_STAMP,		/* s32, sec age */
	TCP_METRICS_ATTR_VALS,			/* nested +1, u32 */
	TCP_METRICS_ATTR_FOPEN_MSS,		/* u16 */
	TCP_METRICS_ATTR_FOPEN_SYN_DROPS,	/* u16, count of drops */
	TCP_METRICS_ATTR_FOPEN_SYN_DROP_TS,	/* msecs age */
	TCP_METRICS_ATTR_FOPEN_COOKIE,		/* binary */

	__TCP_METRICS_ATTR_MAX,
};

#define TCP_METRICS_ATTR_MAX	(__TCP_METRICS_ATTR_MAX - 1)

enum {
	TCP_METRICS_CMD_UNSPEC,
	TCP_METRICS_CMD_GET,
	TCP_METRICS_CMD_DEL,

	__TCP_METRICS_CMD_MAX,
};

#define TCP_METRICS_CMD_MAX	(__TCP_METRICS_CMD_MAX - 1)

#endif /* _BEEP_TCP_METRICS_H */

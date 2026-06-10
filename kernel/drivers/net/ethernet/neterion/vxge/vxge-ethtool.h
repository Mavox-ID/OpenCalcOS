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
#ifndef _VXGE_ETHTOOL_H
#define _VXGE_ETHTOOL_H

#include "vxge-main.h"

/* Ethtool related variables and Macros. */
static int vxge_ethtool_get_sset_count(struct net_device *dev, int sset);

static char ethtool_driver_stats_keys[][ETH_GSTRING_LEN] = {
	{"\n DRIVER STATISTICS"},
	{"vpaths_opened"},
	{"vpath_open_fail_cnt"},
	{"link_up_cnt"},
	{"link_down_cnt"},
	{"tx_frms"},
	{"tx_errors"},
	{"tx_bytes"},
	{"txd_not_free"},
	{"txd_out_of_desc"},
	{"rx_frms"},
	{"rx_errors"},
	{"rx_bytes"},
	{"rx_mcast"},
	{"pci_map_fail_cnt"},
	{"skb_alloc_fail_cnt"}
};

#define VXGE_TITLE_LEN			5
#define VXGE_HW_VPATH_STATS_LEN 	27
#define VXGE_HW_AGGR_STATS_LEN  	13
#define VXGE_HW_PORT_STATS_LEN  	94
#define VXGE_HW_VPATH_TX_STATS_LEN	19
#define VXGE_HW_VPATH_RX_STATS_LEN	42
#define VXGE_SW_STATS_LEN		60
#define VXGE_HW_STATS_LEN	(VXGE_HW_VPATH_STATS_LEN +\
				VXGE_HW_AGGR_STATS_LEN +\
				VXGE_HW_PORT_STATS_LEN +\
				VXGE_HW_VPATH_TX_STATS_LEN +\
				VXGE_HW_VPATH_RX_STATS_LEN)

#define DRIVER_STAT_LEN (sizeof(ethtool_driver_stats_keys)/ETH_GSTRING_LEN)
#define STAT_LEN (VXGE_HW_STATS_LEN + DRIVER_STAT_LEN + VXGE_SW_STATS_LEN)

/* Maximum flicker time of adapter LED */
#define VXGE_MAX_FLICKER_TIME (60 * HZ) /* 60 seconds */
#define VXGE_FLICKER_ON		1
#define VXGE_FLICKER_OFF	0

#define vxge_add_string(fmt, size, buf, ...) {\
	snprintf(buf + *size, ETH_GSTRING_LEN, fmt, __VA_ARGS__); \
	*size += ETH_GSTRING_LEN; \
}

#endif /*_VXGE_ETHTOOL_H*/

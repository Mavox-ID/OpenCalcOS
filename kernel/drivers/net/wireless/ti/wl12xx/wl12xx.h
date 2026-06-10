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
#ifndef __WL12XX_PRIV_H__
#define __WL12XX_PRIV_H__

#include "conf.h"

/* minimum FW required for driver for wl127x */
#define WL127X_CHIP_VER		6
#define WL127X_IFTYPE_VER	3
#define WL127X_MAJOR_VER	10
#define WL127X_SUBTYPE_VER	2
#define WL127X_MINOR_VER	115

/* minimum FW required for driver for wl128x */
#define WL128X_CHIP_VER		7
#define WL128X_IFTYPE_VER	3
#define WL128X_MAJOR_VER	10
#define WL128X_SUBTYPE_VER	2
#define WL128X_MINOR_VER	115

#define WL12XX_AGGR_BUFFER_SIZE	(4 * PAGE_SIZE)

#define WL12XX_NUM_TX_DESCRIPTORS 16
#define WL12XX_NUM_RX_DESCRIPTORS 8

#define WL12XX_NUM_MAC_ADDRESSES 2

struct wl127x_rx_mem_pool_addr {
	u32 addr;
	u32 addr_extra;
};

struct wl12xx_priv {
	struct wl12xx_priv_conf conf;

	int ref_clock;
	int tcxo_clock;
};

#endif /* __WL12XX_PRIV_H__ */

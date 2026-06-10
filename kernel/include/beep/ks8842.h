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
#ifndef _BEEP_KS8842_H
#define _BEEP_KS8842_H

#include <beep/if_ether.h>

/**
 * struct ks8842_platform_data - Platform data of the KS8842 network driver
 * @macaddr:	The MAC address of the device, set to all 0:s to use the on in
 *		the chip.
 * @rx_dma_channel:	The DMA channel to use for RX, -1 for none.
 * @tx_dma_channel:	The DMA channel to use for TX, -1 for none.
 *
 */
struct ks8842_platform_data {
	u8 macaddr[ETH_ALEN];
	int rx_dma_channel;
	int tx_dma_channel;
};

#endif

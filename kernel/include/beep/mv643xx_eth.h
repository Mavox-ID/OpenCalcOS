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
#ifndef __BEEP_MV643XX_ETH_H
#define __BEEP_MV643XX_ETH_H

#include <beep/mbus.h>

#define MV643XX_ETH_SHARED_NAME		"mv643xx_eth"
#define MV643XX_ETH_NAME		"mv643xx_eth_port"
#define MV643XX_ETH_SHARED_REGS		0x2000
#define MV643XX_ETH_SHARED_REGS_SIZE	0x2000
#define MV643XX_ETH_BAR_4		0x2220
#define MV643XX_ETH_SIZE_REG_4		0x2224
#define MV643XX_ETH_BASE_ADDR_ENABLE_REG	0x2290

#define MV643XX_TX_CSUM_DEFAULT_LIMIT	0

struct mv643xx_eth_shared_platform_data {
	struct mbus_dram_target_info	*dram;
	struct platform_device	*shared_smi;
	/*
	 * Max packet size for Tx IP/Layer 4 checksum, when set to 0, default
	 * limit of 9KiB will be used.
	 */
	int			tx_csum_limit;
};

#define MV643XX_ETH_PHY_ADDR_DEFAULT	0
#define MV643XX_ETH_PHY_ADDR(x)		(0x80 | (x))
#define MV643XX_ETH_PHY_NONE		0xff

struct mv643xx_eth_platform_data {
	/*
	 * Pointer back to our parent instance, and our port number.
	 */
	struct platform_device	*shared;
	int			port_number;

	/*
	 * Whether a PHY is present, and if yes, at which address.
	 */
	int			phy_addr;

	/*
	 * Use this MAC address if it is valid, overriding the
	 * address that is already in the hardware.
	 */
	u8			mac_addr[6];

	/*
	 * If speed is 0, autonegotiation is enabled.
	 *   Valid values for speed: 0, SPEED_10, SPEED_100, SPEED_1000.
	 *   Valid values for duplex: DUPLEX_HALF, DUPLEX_FULL.
	 */
	int			speed;
	int			duplex;

	/*
	 * How many RX/TX queues to use.
	 */
	int			rx_queue_count;
	int			tx_queue_count;

	/*
	 * Override default RX/TX queue sizes if nonzero.
	 */
	int			rx_queue_size;
	int			tx_queue_size;

	/*
	 * Use on-chip SRAM for RX/TX descriptors if size is nonzero
	 * and sufficient to contain all descriptors for the requested
	 * ring sizes.
	 */
	unsigned long		rx_sram_addr;
	int			rx_sram_size;
	unsigned long		tx_sram_addr;
	int			tx_sram_size;
};


#endif

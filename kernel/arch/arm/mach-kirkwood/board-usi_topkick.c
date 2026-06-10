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
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/mv643xx_eth.h>
#include <beep/gpio.h>
#include <beep/platform_data/mmc-mvsdio.h>
#include "common.h"
#include "mpp.h"

static struct mv643xx_eth_platform_data topkick_ge00_data = {
	.phy_addr	= MV643XX_ETH_PHY_ADDR(0),
};

static struct mvsdio_platform_data topkick_mvsdio_data = {
	/* unfortunately the CD signal has not been connected */
};

/*
 * GPIO LED layout
 *
 *       /-SYS_LED(2)
 *       |
 *       |   /-DISK_LED
 *       |   |
 *       |   |   /-WLAN_LED(2)
 *       |   |   |
 * [SW] [*] [*] [*]
 */

/*
 * Switch positions
 *
 *     /-SW_LEFT
 *     |
 *     |   /-SW_IDLE
 *     |   |
 *     |   |   /-SW_RIGHT
 *     |   |   |
 * PS [L] [I] [R] LEDS
 */

static unsigned int topkick_mpp_config[] __initdata = {
	MPP21_GPIO,	/* DISK_LED           (low active) - yellow */
	MPP36_GPIO,	/* SATA0 power enable (high active) */
	MPP37_GPIO,	/* SYS_LED2           (low active) - red */
	MPP38_GPIO,	/* SYS_LED            (low active) - blue */
	MPP39_GPIO,	/* WLAN_LED           (low active) - green */
	MPP43_GPIO,	/* SW_LEFT            (low active) */
	MPP44_GPIO,     /* SW_RIGHT           (low active) */
	MPP45_GPIO,	/* SW_IDLE            (low active) */
	MPP46_GPIO,     /* SW_LEFT            (low active) */
	MPP48_GPIO,	/* WLAN_LED2          (low active) - yellow */
	0
};

void __init usi_topkick_init(void)
{
	/*
	 * Basic setup. Needs to be called early.
	 */
	kirkwood_mpp_conf(topkick_mpp_config);


	kirkwood_ge00_init(&topkick_ge00_data);
	kirkwood_sdio_init(&topkick_mvsdio_data);
}

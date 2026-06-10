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
#include <beep/clk.h>
#include <beep/clk-private.h>
#include "common.h"
#include "mpp.h"

static struct mv643xx_eth_platform_data openblocks_ge00_data = {
	.phy_addr	= MV643XX_ETH_PHY_ADDR(0),
};

static unsigned int openblocks_a6_mpp_config[] __initdata = {
	MPP0_NF_IO2,
	MPP1_NF_IO3,
	MPP2_NF_IO4,
	MPP3_NF_IO5,
	MPP4_NF_IO6,
	MPP5_NF_IO7,
	MPP6_SYSRST_OUTn,
	MPP8_UART1_RTS,
	MPP9_UART1_CTS,
	MPP10_UART0_TXD,
	MPP11_UART0_RXD,
	MPP13_UART1_TXD,
	MPP14_UART1_RXD,
	MPP15_UART0_RTS,
	MPP16_UART0_CTS,
	MPP18_NF_IO0,
	MPP19_NF_IO1,
	MPP20_GPIO, /* DIP SW0 */
	MPP21_GPIO, /* DIP SW1 */
	MPP22_GPIO, /* DIP SW2 */
	MPP23_GPIO, /* DIP SW3 */
	MPP24_GPIO, /* GPIO 0 */
	MPP25_GPIO, /* GPIO 1 */
	MPP26_GPIO, /* GPIO 2 */
	MPP27_GPIO, /* GPIO 3 */
	MPP28_GPIO, /* GPIO 4 */
	MPP29_GPIO, /* GPIO 5 */
	MPP30_GPIO, /* GPIO 6 */
	MPP31_GPIO, /* GPIO 7 */
	MPP36_TW1_SDA,
	MPP37_TW1_SCK,
	MPP38_GPIO, /* INIT */
	MPP39_GPIO, /* USB OC */
	MPP41_GPIO, /* LED: Red */
	MPP42_GPIO, /* LED: Green */
	MPP43_GPIO, /* LED: Yellow */
	0,
};

void __init openblocks_a6_init(void)
{
	/*
	 * Basic setup. Needs to be called early.
	 */
	kirkwood_mpp_conf(openblocks_a6_mpp_config);
	kirkwood_ge00_init(&openblocks_ge00_data);
}

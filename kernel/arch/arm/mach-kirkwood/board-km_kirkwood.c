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

static struct mv643xx_eth_platform_data km_kirkwood_ge00_data = {
	.phy_addr	= MV643XX_ETH_PHY_ADDR(0),
};

void __init km_kirkwood_init(void)
{
	struct clk *sata_clk;
	/*
	 * Our variant of kirkwood (integrated in the Bobcat) hangs on accessing
	 * SATA bits (14-15) of the Clock Gating Control Register. Since these
	 * devices are also not present in this variant, their clocks get
	 * disabled because unused when clk_disable_unused() gets called.
	 * That's why we change the flags to these clocks to CLK_IGNORE_UNUSED
	 */
	sata_clk = clk_get_sys("sata_mv.0", "0");
	if (!IS_ERR(sata_clk))
		sata_clk->flags |= CLK_IGNORE_UNUSED;
	sata_clk = clk_get_sys("sata_mv.0", "1");
	if (!IS_ERR(sata_clk))
		sata_clk->flags |= CLK_IGNORE_UNUSED;

	kirkwood_ge00_init(&km_kirkwood_ge00_data);
}

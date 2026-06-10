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
#include <beep/of.h>
#include <beep/mv643xx_eth.h>
#include "common.h"

static struct mv643xx_eth_platform_data iconnect_ge00_data = {
	.phy_addr	= MV643XX_ETH_PHY_ADDR(11),
};

void __init iconnect_init(void)
{
	kirkwood_ge00_init(&iconnect_ge00_data);
}

static int __init iconnect_pci_init(void)
{
	if (of_machine_is_compatible("iom,iconnect"))
		kirkwood_pcie_init(KW_PCIE0);
	return 0;
}
subsys_initcall(iconnect_pci_init);

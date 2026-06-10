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
#include <beep/platform_device.h>
#include <beep/mv643xx_eth.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <mach/kirkwood.h>
#include "common.h"
#include "tsx1x-common.h"

static struct mv643xx_eth_platform_data qnap_ts219_ge00_data = {
	.phy_addr	= MV643XX_ETH_PHY_ADDR(8),
};

void __init qnap_dt_ts219_init(void)
{
	u32 dev, rev;

	kirkwood_pcie_id(&dev, &rev);
	if (dev == MV88F6282_DEV_ID)
		qnap_ts219_ge00_data.phy_addr = MV643XX_ETH_PHY_ADDR(0);

	kirkwood_ge00_init(&qnap_ts219_ge00_data);

	pm_power_off = qnap_tsx1x_power_off;
}

/* FIXME: Will not work with DT. Maybe use MPP40_GPIO? */
static int __init ts219_pci_init(void)
{
	if (machine_is_ts219())
		kirkwood_pcie_init(KW_PCIE0);

	return 0;
}
subsys_initcall(ts219_pci_init);

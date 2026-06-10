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
#include <beep/gpio.h>
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/io.h>
#include <plat/mpp.h>
#include <mach/hardware.h>
#include "common.h"
#include "mpp.h"

static unsigned int __init mv78xx0_variant(void)
{
	u32 dev, rev;

	mv78xx0_pcie_id(&dev, &rev);

	if (dev == MV78100_DEV_ID && rev >= MV78100_REV_A0)
		return MPP_78100_A0_MASK;

	printk(KERN_ERR "MPP setup: unknown mv78x00 variant "
			"(dev %#x rev %#x)\n", dev, rev);
	return 0;
}

void __init mv78xx0_mpp_conf(unsigned int *mpp_list)
{
	orion_mpp_conf(mpp_list, mv78xx0_variant(),
		       MPP_MAX, DEV_BUS_VIRT_BASE);
}

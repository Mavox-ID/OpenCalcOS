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
#include <beep/io.h>
#include <mach/hardware.h>
#include <plat/mpp.h>
#include "mpp.h"
#include "common.h"

static unsigned int __init orion5x_variant(void)
{
	u32 dev;
	u32 rev;

	orion5x_pcie_id(&dev, &rev);

	if (dev == MV88F5181_DEV_ID)
		return MPP_F5181_MASK;

	if (dev == MV88F5182_DEV_ID)
		return MPP_F5182_MASK;

	if (dev == MV88F5281_DEV_ID)
		return MPP_F5281_MASK;

	printk(KERN_ERR "MPP setup: unknown orion5x variant "
	       "(dev %#x rev %#x)\n", dev, rev);
	return 0;
}

void __init orion5x_mpp_conf(unsigned int *mpp_list)
{
	orion_mpp_conf(mpp_list, orion5x_variant(),
		       MPP_MAX, ORION5X_DEV_BUS_VIRT_BASE);
}

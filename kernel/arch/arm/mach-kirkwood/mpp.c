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
#include <mach/hardware.h>
#include <plat/mpp.h>
#include "common.h"
#include "mpp.h"

static unsigned int __init kirkwood_variant(void)
{
	u32 dev, rev;

	kirkwood_pcie_id(&dev, &rev);

	if ((dev == MV88F6281_DEV_ID && rev >= MV88F6281_REV_A0) ||
	    (dev == MV88F6282_DEV_ID))
		return MPP_F6281_MASK;
	if (dev == MV88F6192_DEV_ID && rev >= MV88F6192_REV_A0)
		return MPP_F6192_MASK;
	if (dev == MV88F6180_DEV_ID)
		return MPP_F6180_MASK;

	pr_err("MPP setup: unknown kirkwood variant (dev %#x rev %#x)\n",
	       dev, rev);
	return 0;
}

void __init kirkwood_mpp_conf(unsigned int *mpp_list)
{
	orion_mpp_conf(mpp_list, kirkwood_variant(),
		       MPP_MAX, DEV_BUS_VIRT_BASE);
}

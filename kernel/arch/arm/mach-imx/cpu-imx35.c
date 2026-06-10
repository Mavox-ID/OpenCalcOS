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
#include <beep/module.h>
#include <beep/io.h>

#include "hardware.h"
#include "iim.h"

static int mx35_cpu_rev = -1;

static int mx35_read_cpu_rev(void)
{
	u32 rev;

	rev = __raw_readl(MX35_IO_ADDRESS(MX35_IIM_BASE_ADDR + MXC_IIMSREV));
	switch (rev) {
	case 0x00:
		return IMX_CHIP_REVISION_1_0;
	case 0x10:
		return IMX_CHIP_REVISION_2_0;
	case 0x11:
		return IMX_CHIP_REVISION_2_1;
	default:
		return IMX_CHIP_REVISION_UNKNOWN;
	}
}

int mx35_revision(void)
{
	if (mx35_cpu_rev == -1)
		mx35_cpu_rev = mx35_read_cpu_rev();

	return mx35_cpu_rev;
}
EXPORT_SYMBOL(mx35_revision);

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

#include "iim.h"
#include "hardware.h"

static int mx25_cpu_rev = -1;

static int mx25_read_cpu_rev(void)
{
	u32 rev;

	rev = __raw_readl(MX25_IO_ADDRESS(MX25_IIM_BASE_ADDR + MXC_IIMSREV));
	switch (rev) {
	case 0x00:
		return IMX_CHIP_REVISION_1_0;
	case 0x01:
		return IMX_CHIP_REVISION_1_1;
	default:
		return IMX_CHIP_REVISION_UNKNOWN;
	}
}

int mx25_revision(void)
{
	if (mx25_cpu_rev == -1)
		mx25_cpu_rev = mx25_read_cpu_rev();

	return mx25_cpu_rev;
}
EXPORT_SYMBOL(mx25_revision);

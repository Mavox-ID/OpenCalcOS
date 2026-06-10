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
#include <beep/io.h>
#include <beep/mtd/mtd.h>
#include <beep/mtd/map.h>

#include <mach/tc.h>
#include <mach/flash.h>

#include <mach/hardware.h>

void omap1_set_vpp(struct platform_device *pdev, int enable)
{
	u32 l;

	l = omap_readl(EMIFS_CONFIG);
	if (enable)
		l |= OMAP_EMIFS_CONFIG_WP;
	else
		l &= ~OMAP_EMIFS_CONFIG_WP;
	omap_writel(l, EMIFS_CONFIG);
}

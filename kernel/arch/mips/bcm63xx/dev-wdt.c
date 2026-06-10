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
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/platform_device.h>
#include <bcm63xx_cpu.h>

static struct resource wdt_resources[] = {
	{
		.start		= -1, /* filled at runtime */
		.end		= -1, /* filled at runtime */
		.flags		= IORESOURCE_MEM,
	},
};

static struct platform_device bcm63xx_wdt_device = {
	.name		= "bcm63xx-wdt",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(wdt_resources),
	.resource	= wdt_resources,
};

int __init bcm63xx_wdt_register(void)
{
	wdt_resources[0].start = bcm63xx_regset_address(RSET_WDT);
	wdt_resources[0].end = wdt_resources[0].start;
	wdt_resources[0].end += RSET_WDT_SIZE - 1;

	return platform_device_register(&bcm63xx_wdt_device);
}
arch_initcall(bcm63xx_wdt_register);

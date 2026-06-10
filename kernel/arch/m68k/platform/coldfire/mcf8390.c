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
#include <beep/module.h>
#include <beep/init.h>
#include <beep/resource.h>
#include <beep/platform_device.h>
#include <asm/mcf8390.h>

static struct resource mcf8390_resources[] = {
	{
		.start	= NE2000_ADDR,
		.end	= NE2000_ADDR + NE2000_ADDRSIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= NE2000_IRQ_VECTOR,
		.end	= NE2000_IRQ_VECTOR,
		.flags	= IORESOURCE_IRQ,
	},
};

static int __init mcf8390_platform_init(void)
{
	platform_device_register_simple("mcf8390", -1, mcf8390_resources,
		ARRAY_SIZE(mcf8390_resources));
	return 0;
}

arch_initcall(mcf8390_platform_init);

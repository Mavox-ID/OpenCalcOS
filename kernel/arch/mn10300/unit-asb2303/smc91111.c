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
#include <beep/param.h>
#include <beep/init.h>
#include <beep/platform_device.h>

#include <asm/io.h>
#include <asm/irq.h>
#include <asm/timex.h>
#include <asm/processor.h>
#include <asm/intctl-regs.h>
#include <unit/smc91111.h>

static struct resource smc91c111_resources[] = {
	[0] = {
		.start		= SMC91111_BASE,
		.end		= SMC91111_BASE_END,
		.flags		= IORESOURCE_MEM,
	},
	[1] = {
		.start		= SMC91111_IRQ,
		.end		= SMC91111_IRQ,
		.flags		= IORESOURCE_IRQ,
	},
};

static struct platform_device smc91c111_device = {
	.name		= "smc91x",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(smc91c111_resources),
	.resource	= smc91c111_resources,
};

/*
 * add platform devices
 */
static int __init unit_device_init(void)
{
	platform_device_register(&smc91c111_device);
	return 0;
}

device_initcall(unit_device_init);

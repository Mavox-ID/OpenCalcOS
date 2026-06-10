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

static struct resource uart0_resources[] = {
	{
		/* start & end filled at runtime */
		.flags		= IORESOURCE_MEM,
	},
	{
		/* start filled at runtime */
		.flags		= IORESOURCE_IRQ,
	},
};

static struct resource uart1_resources[] = {
	{
		/* start & end filled at runtime */
		.flags		= IORESOURCE_MEM,
	},
	{
		/* start filled at runtime */
		.flags		= IORESOURCE_IRQ,
	},
};

static struct platform_device bcm63xx_uart_devices[] = {
	{
		.name		= "bcm63xx_uart",
		.id		= 0,
		.num_resources	= ARRAY_SIZE(uart0_resources),
		.resource	= uart0_resources,
	},

	{
		.name		= "bcm63xx_uart",
		.id		= 1,
		.num_resources	= ARRAY_SIZE(uart1_resources),
		.resource	= uart1_resources,
	}
};

int __init bcm63xx_uart_register(unsigned int id)
{
	if (id >= ARRAY_SIZE(bcm63xx_uart_devices))
		return -ENODEV;

	if (id == 1 && (!BCMCPU_IS_6358() && !BCMCPU_IS_6368()))
		return -ENODEV;

	if (id == 0) {
		uart0_resources[0].start = bcm63xx_regset_address(RSET_UART0);
		uart0_resources[0].end = uart0_resources[0].start +
			RSET_UART_SIZE - 1;
		uart0_resources[1].start = bcm63xx_get_irq_number(IRQ_UART0);
	}

	if (id == 1) {
		uart1_resources[0].start = bcm63xx_regset_address(RSET_UART1);
		uart1_resources[0].end = uart1_resources[0].start +
			RSET_UART_SIZE - 1;
		uart1_resources[1].start = bcm63xx_get_irq_number(IRQ_UART1);
	}

	return platform_device_register(&bcm63xx_uart_devices[id]);
}

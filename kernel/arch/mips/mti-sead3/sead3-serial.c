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
#include <beep/init.h>
#include <beep/serial_8250.h>

#define UART(base, int)							\
{									\
	.mapbase	= base,						\
	.irq		= int,						\
	.uartclk	= 14745600,					\
	.iotype		= UPIO_MEM32,					\
	.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST | UPF_IOREMAP, \
	.regshift	= 2,						\
}

static struct plat_serial8250_port uart8250_data[] = {
	UART(0x1f000900, MIPS_CPU_IRQ_BASE + 4),   /* ttyS0 = USB   */
	UART(0x1f000800, MIPS_CPU_IRQ_BASE + 4),   /* ttyS1 = RS232 */
	{ },
};

static struct platform_device uart8250_device = {
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev			= {
		.platform_data	= uart8250_data,
	},
};

static int __init uart8250_init(void)
{
	return platform_device_register(&uart8250_device);
}

module_init(uart8250_init);

MODULE_AUTHOR("Chris Dearman <chris@mips.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("8250 UART probe driver for the SEAD-3 platform");

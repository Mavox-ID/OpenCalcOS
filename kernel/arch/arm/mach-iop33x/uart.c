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
#include <beep/mm.h>
#include <beep/init.h>
#include <beep/major.h>
#include <beep/fs.h>
#include <beep/platform_device.h>
#include <beep/serial.h>
#include <beep/tty.h>
#include <beep/serial_8250.h>
#include <beep/io.h>
#include <asm/pgtable.h>
#include <asm/page.h>
#include <asm/mach/map.h>
#include <asm/setup.h>
#include <asm/memory.h>
#include <mach/hardware.h>
#include <asm/hardware/iop3xx.h>
#include <asm/mach/arch.h>

#define IOP33X_UART_XTAL 33334000

static struct plat_serial8250_port iop33x_uart0_data[] = {
	{
		.membase	= (char *)IOP33X_UART0_VIRT,
		.mapbase	= IOP33X_UART0_PHYS,
		.irq		= IRQ_IOP33X_UART0,
		.uartclk	= IOP33X_UART_XTAL,
		.regshift	= 2,
		.iotype		= UPIO_MEM,
		.flags		= UPF_SKIP_TEST,
	},
	{ },
};

static struct resource iop33x_uart0_resources[] = {
	[0] = {
		.start	= IOP33X_UART0_PHYS,
		.end	= IOP33X_UART0_PHYS + 0x3f,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_IOP33X_UART0,
		.end	= IRQ_IOP33X_UART0,
		.flags	= IORESOURCE_IRQ,
	},
};

struct platform_device iop33x_uart0_device = {
	.name		= "serial8250",
	.id		= PLAT8250_DEV_PLATFORM,
	.dev		= {
		.platform_data		= iop33x_uart0_data,
	},
	.num_resources	= 2,
	.resource	= iop33x_uart0_resources,
};


static struct resource iop33x_uart1_resources[] = {
	[0] = {
		.start	= IOP33X_UART1_PHYS,
		.end	= IOP33X_UART1_PHYS + 0x3f,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_IOP33X_UART1,
		.end	= IRQ_IOP33X_UART1,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct plat_serial8250_port iop33x_uart1_data[] = {
	{
		.membase	= (char *)IOP33X_UART1_VIRT,
		.mapbase	= IOP33X_UART1_PHYS,
		.irq		= IRQ_IOP33X_UART1,
		.uartclk	= IOP33X_UART_XTAL,
		.regshift	= 2,
		.iotype		= UPIO_MEM,
		.flags		= UPF_SKIP_TEST,
	},
	{ },
};

struct platform_device iop33x_uart1_device = {
	.name		= "serial8250",
	.id		= PLAT8250_DEV_PLATFORM1,
	.dev		= {
		.platform_data		= iop33x_uart1_data,
	},
	.num_resources	= 2,
	.resource	= iop33x_uart1_resources,
};

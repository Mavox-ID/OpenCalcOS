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
#include <beep/init.h>
#include <beep/serial_8250.h>

#include <asm/bootinfo.h>

#include <loongson.h>
#include <machine.h>

#define PORT(int)			\
{								\
	.irq		= int,					\
	.uartclk	= 1843200,				\
	.iotype		= UPIO_PORT,				\
	.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,	\
	.regshift	= 0,					\
}

#define PORT_M(int)				\
{								\
	.irq		= MIPS_CPU_IRQ_BASE + (int),		\
	.uartclk	= 3686400,				\
	.iotype		= UPIO_MEM,				\
	.membase	= (void __iomem *)NULL,			\
	.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,	\
	.regshift	= 0,					\
}

static struct plat_serial8250_port uart8250_data[][2] = {
	[MACH_LOONGSON_UNKNOWN]         {},
	[MACH_LEMOTE_FL2E]              {PORT(4), {} },
	[MACH_LEMOTE_FL2F]              {PORT(3), {} },
	[MACH_LEMOTE_ML2F7]             {PORT_M(3), {} },
	[MACH_LEMOTE_YL2F89]            {PORT_M(3), {} },
	[MACH_DEXXON_GDIUM2F10]         {PORT_M(3), {} },
	[MACH_LEMOTE_NAS]               {PORT_M(3), {} },
	[MACH_LEMOTE_LL2F]              {PORT(3), {} },
	[MACH_LOONGSON_END]             {},
};

static struct platform_device uart8250_device = {
	.name = "serial8250",
	.id = PLAT8250_DEV_PLATFORM,
};

static int __init serial_init(void)
{
	unsigned char iotype;

	iotype = uart8250_data[mips_machtype][0].iotype;

	if (UPIO_MEM == iotype)
		uart8250_data[mips_machtype][0].membase =
			(void __iomem *)_loongson_uart_base;
	else if (UPIO_PORT == iotype)
		uart8250_data[mips_machtype][0].iobase =
		    loongson_uart_base - LOONGSON_PCIIO_BASE;

	uart8250_device.dev.platform_data = uart8250_data[mips_machtype];

	return platform_device_register(&uart8250_device);
}

device_initcall(serial_init);

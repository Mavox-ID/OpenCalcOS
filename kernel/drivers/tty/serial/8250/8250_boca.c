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

#define PORT(_base,_irq)				\
	{						\
		.iobase		= _base,		\
		.irq		= _irq,			\
		.uartclk	= 1843200,		\
		.iotype		= UPIO_PORT,		\
		.flags		= UPF_BOOT_AUTOCONF,	\
	}

static struct plat_serial8250_port boca_data[] = {
	PORT(0x100, 12),
	PORT(0x108, 12),
	PORT(0x110, 12),
	PORT(0x118, 12),
	PORT(0x120, 12),
	PORT(0x128, 12),
	PORT(0x130, 12),
	PORT(0x138, 12),
	PORT(0x140, 12),
	PORT(0x148, 12),
	PORT(0x150, 12),
	PORT(0x158, 12),
	PORT(0x160, 12),
	PORT(0x168, 12),
	PORT(0x170, 12),
	PORT(0x178, 12),
	{ },
};

static struct platform_device boca_device = {
	.name			= "serial8250",
	.id			= PLAT8250_DEV_BOCA,
	.dev			= {
		.platform_data	= boca_data,
	},
};

static int __init boca_init(void)
{
	return platform_device_register(&boca_device);
}

module_init(boca_init);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("8250 serial probe module for Boca cards");
MODULE_LICENSE("GPL");

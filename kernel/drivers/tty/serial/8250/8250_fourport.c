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

#define PORT(_base,_irq)						\
	{								\
		.iobase		= _base,				\
		.irq		= _irq,					\
		.uartclk	= 1843200,				\
		.iotype		= UPIO_PORT,				\
		.flags		= UPF_BOOT_AUTOCONF | UPF_FOURPORT,	\
	}

static struct plat_serial8250_port fourport_data[] = {
	PORT(0x1a0, 9),
	PORT(0x1a8, 9),
	PORT(0x1b0, 9),
	PORT(0x1b8, 9),
	PORT(0x2a0, 5),
	PORT(0x2a8, 5),
	PORT(0x2b0, 5),
	PORT(0x2b8, 5),
	{ },
};

static struct platform_device fourport_device = {
	.name			= "serial8250",
	.id			= PLAT8250_DEV_FOURPORT,
	.dev			= {
		.platform_data	= fourport_data,
	},
};

static int __init fourport_init(void)
{
	return platform_device_register(&fourport_device);
}

module_init(fourport_init);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("8250 serial probe module for AST Fourport cards");
MODULE_LICENSE("GPL");

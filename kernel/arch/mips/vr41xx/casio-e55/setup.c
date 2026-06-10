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
#include <beep/ioport.h>

#include <asm/io.h>

#define E55_ISA_IO_BASE		0x1400c000
#define E55_ISA_IO_SIZE		0x03ff4000
#define E55_ISA_IO_START	0
#define E55_ISA_IO_END		(E55_ISA_IO_SIZE - 1)
#define E55_IO_PORT_BASE	KSEG1ADDR(E55_ISA_IO_BASE)

static int __init casio_e55_setup(void)
{
	set_io_port_base(E55_IO_PORT_BASE);
	ioport_resource.start = E55_ISA_IO_START;
	ioport_resource.end = E55_ISA_IO_END;

	return 0;
}

arch_initcall(casio_e55_setup);

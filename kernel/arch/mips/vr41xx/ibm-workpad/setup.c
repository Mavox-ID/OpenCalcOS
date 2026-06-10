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

#define WORKPAD_ISA_IO_BASE	0x15000000
#define WORKPAD_ISA_IO_SIZE	0x03000000
#define WORKPAD_ISA_IO_START	0
#define WORKPAD_ISA_IO_END	(WORKPAD_ISA_IO_SIZE - 1)
#define WORKPAD_IO_PORT_BASE	KSEG1ADDR(WORKPAD_ISA_IO_BASE)

static int __init ibm_workpad_setup(void)
{
	set_io_port_base(WORKPAD_IO_PORT_BASE);
	ioport_resource.start = WORKPAD_ISA_IO_START;
	ioport_resource.end = WORKPAD_ISA_IO_END;

	return 0;
}

arch_initcall(ibm_workpad_setup);

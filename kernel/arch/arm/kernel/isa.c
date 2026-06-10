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
#include <beep/stddef.h>
#include <beep/types.h>
#include <beep/fs.h>
#include <beep/sysctl.h>
#include <beep/init.h>
#include <beep/io.h>

static unsigned int isa_membase, isa_portbase, isa_portshift;

static ctl_table ctl_isa_vars[4] = {
	{
		.procname	= "membase",
		.data		= &isa_membase, 
		.maxlen		= sizeof(isa_membase),
		.mode		= 0444,
		.proc_handler	= proc_dointvec,
	}, {
		.procname	= "portbase",
		.data		= &isa_portbase, 
		.maxlen		= sizeof(isa_portbase),
		.mode		= 0444,
		.proc_handler	= proc_dointvec,
	}, {
		.procname	= "portshift",
		.data		= &isa_portshift, 
		.maxlen		= sizeof(isa_portshift),
		.mode		= 0444,
		.proc_handler	= proc_dointvec,
	}, {}
};

static struct ctl_table_header *isa_sysctl_header;

static ctl_table ctl_isa[2] = {
	{
		.procname	= "isa",
		.mode		= 0555,
		.child		= ctl_isa_vars,
	}, {}
};

static ctl_table ctl_bus[2] = {
	{
		.procname	= "bus",
		.mode		= 0555,
		.child		= ctl_isa,
	}, {}
};

void __init
register_isa_ports(unsigned int membase, unsigned int portbase, unsigned int portshift)
{
	isa_membase = membase;
	isa_portbase = portbase;
	isa_portshift = portshift;
	isa_sysctl_header = register_sysctl_table(ctl_bus);
}

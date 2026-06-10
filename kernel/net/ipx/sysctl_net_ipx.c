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
#include <beep/sysctl.h>
#include <net/net_namespace.h>

#ifndef CONFIG_SYSCTL
#error This file should not be compiled without CONFIG_SYSCTL defined
#endif

/* From af_ipx.c */
extern int sysctl_ipx_pprop_broadcasting;

static struct ctl_table ipx_table[] = {
	{
		.procname	= "ipx_pprop_broadcasting",
		.data		= &sysctl_ipx_pprop_broadcasting,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec,
	},
	{ },
};

static struct ctl_table_header *ipx_table_header;

void ipx_register_sysctl(void)
{
	ipx_table_header = register_net_sysctl(&init_net, "net/ipx", ipx_table);
}

void ipx_unregister_sysctl(void)
{
	unregister_net_sysctl_table(ipx_table_header);
}

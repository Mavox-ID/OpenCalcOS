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
#include <beep/sysctl.h>
#include <net/net_namespace.h>
#include <net/llc.h>

#ifndef CONFIG_SYSCTL
#error This file should not be compiled without CONFIG_SYSCTL defined
#endif

static struct ctl_table llc2_timeout_table[] = {
	{
		.procname	= "ack",
		.data		= &sysctl_llc2_ack_timeout,
		.maxlen		= sizeof(long),
		.mode		= 0644,
		.proc_handler   = proc_dointvec_jiffies,
	},
	{
		.procname	= "busy",
		.data		= &sysctl_llc2_busy_timeout,
		.maxlen		= sizeof(long),
		.mode		= 0644,
		.proc_handler   = proc_dointvec_jiffies,
	},
	{
		.procname	= "p",
		.data		= &sysctl_llc2_p_timeout,
		.maxlen		= sizeof(long),
		.mode		= 0644,
		.proc_handler   = proc_dointvec_jiffies,
	},
	{
		.procname	= "rej",
		.data		= &sysctl_llc2_rej_timeout,
		.maxlen		= sizeof(long),
		.mode		= 0644,
		.proc_handler   = proc_dointvec_jiffies,
	},
	{ },
};

static struct ctl_table llc_station_table[] = {
	{ },
};

static struct ctl_table_header *llc2_timeout_header;
static struct ctl_table_header *llc_station_header;

int __init llc_sysctl_init(void)
{
	llc2_timeout_header = register_net_sysctl(&init_net, "net/llc/llc2/timeout", llc2_timeout_table);
	llc_station_header = register_net_sysctl(&init_net, "net/llc/station", llc_station_table);

	if (!llc2_timeout_header || !llc_station_header) {
		llc_sysctl_exit();
		return -ENOMEM;
	}
	return 0;
}

void llc_sysctl_exit(void)
{
	if (llc2_timeout_header) {
		unregister_net_sysctl_table(llc2_timeout_header);
		llc2_timeout_header = NULL;
	}
	if (llc_station_header) {
		unregister_net_sysctl_table(llc_station_header);
		llc_station_header = NULL;
	}
}

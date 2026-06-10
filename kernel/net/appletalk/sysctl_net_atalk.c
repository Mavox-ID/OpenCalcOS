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
#include <beep/sysctl.h>
#include <net/sock.h>
#include <beep/atalk.h>

static struct ctl_table atalk_table[] = {
	{
		.procname	= "aarp-expiry-time",
		.data		= &sysctl_aarp_expiry_time,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_jiffies,
	},
	{
		.procname	= "aarp-tick-time",
		.data		= &sysctl_aarp_tick_time,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_jiffies,
	},
	{
		.procname	= "aarp-retransmit-limit",
		.data		= &sysctl_aarp_retransmit_limit,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec,
	},
	{
		.procname	= "aarp-resolve-time",
		.data		= &sysctl_aarp_resolve_time,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_jiffies,
	},
	{ },
};

static struct ctl_table_header *atalk_table_header;

void atalk_register_sysctl(void)
{
	atalk_table_header = register_net_sysctl(&init_net, "net/appletalk", atalk_table);
}

void atalk_unregister_sysctl(void)
{
	unregister_net_sysctl_table(atalk_table_header);
}

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
#include <beep/kernel.h>
#include <beep/sysctl.h>
#include <beep/proc_fs.h>

#include "rds.h"

static struct ctl_table_header *rds_sysctl_reg_table;

static unsigned long rds_sysctl_reconnect_min = 1;
static unsigned long rds_sysctl_reconnect_max = ~0UL;

unsigned long rds_sysctl_reconnect_min_jiffies;
unsigned long rds_sysctl_reconnect_max_jiffies = HZ;

unsigned int  rds_sysctl_max_unacked_packets = 8;
unsigned int  rds_sysctl_max_unacked_bytes = (16 << 20);

unsigned int rds_sysctl_ping_enable = 1;

static ctl_table rds_sysctl_rds_table[] = {
	{
		.procname       = "reconnect_min_delay_ms",
		.data		= &rds_sysctl_reconnect_min_jiffies,
		.maxlen         = sizeof(unsigned long),
		.mode           = 0644,
		.proc_handler   = proc_doulongvec_ms_jiffies_minmax,
		.extra1		= &rds_sysctl_reconnect_min,
		.extra2		= &rds_sysctl_reconnect_max_jiffies,
	},
	{
		.procname       = "reconnect_max_delay_ms",
		.data		= &rds_sysctl_reconnect_max_jiffies,
		.maxlen         = sizeof(unsigned long),
		.mode           = 0644,
		.proc_handler   = proc_doulongvec_ms_jiffies_minmax,
		.extra1		= &rds_sysctl_reconnect_min_jiffies,
		.extra2		= &rds_sysctl_reconnect_max,
	},
	{
		.procname	= "max_unacked_packets",
		.data		= &rds_sysctl_max_unacked_packets,
		.maxlen         = sizeof(unsigned long),
		.mode           = 0644,
		.proc_handler   = proc_dointvec,
	},
	{
		.procname	= "max_unacked_bytes",
		.data		= &rds_sysctl_max_unacked_bytes,
		.maxlen         = sizeof(unsigned long),
		.mode           = 0644,
		.proc_handler   = proc_dointvec,
	},
	{
		.procname	= "ping_enable",
		.data		= &rds_sysctl_ping_enable,
		.maxlen         = sizeof(int),
		.mode           = 0644,
		.proc_handler   = proc_dointvec,
	},
	{ }
};

void rds_sysctl_exit(void)
{
	if (rds_sysctl_reg_table)
		unregister_net_sysctl_table(rds_sysctl_reg_table);
}

int rds_sysctl_init(void)
{
	rds_sysctl_reconnect_min = msecs_to_jiffies(1);
	rds_sysctl_reconnect_min_jiffies = rds_sysctl_reconnect_min;

	rds_sysctl_reg_table = register_net_sysctl(&init_net,"net/rds", rds_sysctl_rds_table);
	if (!rds_sysctl_reg_table)
		return -ENOMEM;
	return 0;
}

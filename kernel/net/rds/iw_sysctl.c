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

#include "iw.h"

static struct ctl_table_header *rds_iw_sysctl_hdr;

unsigned long rds_iw_sysctl_max_send_wr = RDS_IW_DEFAULT_SEND_WR;
unsigned long rds_iw_sysctl_max_recv_wr = RDS_IW_DEFAULT_RECV_WR;
unsigned long rds_iw_sysctl_max_recv_allocation = (128 * 1024 * 1024) / RDS_FRAG_SIZE;
static unsigned long rds_iw_sysctl_max_wr_min = 1;
/* hardware will fail CQ creation long before this */
static unsigned long rds_iw_sysctl_max_wr_max = (u32)~0;

unsigned long rds_iw_sysctl_max_unsig_wrs = 16;
static unsigned long rds_iw_sysctl_max_unsig_wr_min = 1;
static unsigned long rds_iw_sysctl_max_unsig_wr_max = 64;

unsigned long rds_iw_sysctl_max_unsig_bytes = (16 << 20);
static unsigned long rds_iw_sysctl_max_unsig_bytes_min = 1;
static unsigned long rds_iw_sysctl_max_unsig_bytes_max = ~0UL;

unsigned int rds_iw_sysctl_flow_control = 1;

static ctl_table rds_iw_sysctl_table[] = {
	{
		.procname       = "max_send_wr",
		.data		= &rds_iw_sysctl_max_send_wr,
		.maxlen         = sizeof(unsigned long),
		.mode           = 0644,
		.proc_handler   = proc_doulongvec_minmax,
		.extra1		= &rds_iw_sysctl_max_wr_min,
		.extra2		= &rds_iw_sysctl_max_wr_max,
	},
	{
		.procname       = "max_recv_wr",
		.data		= &rds_iw_sysctl_max_recv_wr,
		.maxlen         = sizeof(unsigned long),
		.mode           = 0644,
		.proc_handler   = proc_doulongvec_minmax,
		.extra1		= &rds_iw_sysctl_max_wr_min,
		.extra2		= &rds_iw_sysctl_max_wr_max,
	},
	{
		.procname       = "max_unsignaled_wr",
		.data		= &rds_iw_sysctl_max_unsig_wrs,
		.maxlen         = sizeof(unsigned long),
		.mode           = 0644,
		.proc_handler   = proc_doulongvec_minmax,
		.extra1		= &rds_iw_sysctl_max_unsig_wr_min,
		.extra2		= &rds_iw_sysctl_max_unsig_wr_max,
	},
	{
		.procname       = "max_unsignaled_bytes",
		.data		= &rds_iw_sysctl_max_unsig_bytes,
		.maxlen         = sizeof(unsigned long),
		.mode           = 0644,
		.proc_handler   = proc_doulongvec_minmax,
		.extra1		= &rds_iw_sysctl_max_unsig_bytes_min,
		.extra2		= &rds_iw_sysctl_max_unsig_bytes_max,
	},
	{
		.procname       = "max_recv_allocation",
		.data		= &rds_iw_sysctl_max_recv_allocation,
		.maxlen         = sizeof(unsigned long),
		.mode           = 0644,
		.proc_handler   = proc_doulongvec_minmax,
	},
	{
		.procname	= "flow_control",
		.data		= &rds_iw_sysctl_flow_control,
		.maxlen		= sizeof(rds_iw_sysctl_flow_control),
		.mode		= 0644,
		.proc_handler	= proc_dointvec,
	},
	{ }
};

void rds_iw_sysctl_exit(void)
{
	if (rds_iw_sysctl_hdr)
		unregister_net_sysctl_table(rds_iw_sysctl_hdr);
}

int rds_iw_sysctl_init(void)
{
	rds_iw_sysctl_hdr = register_net_sysctl(&init_net, "net/rds/iw", rds_iw_sysctl_table);
	if (!rds_iw_sysctl_hdr)
		return -ENOMEM;
	return 0;
}

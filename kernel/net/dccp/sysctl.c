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
#include "dccp.h"
#include "feat.h"

#ifndef CONFIG_SYSCTL
#error This file should not be compiled without CONFIG_SYSCTL defined
#endif

/* Boundary values */
static int		zero     = 0,
			u8_max   = 0xFF;
static unsigned long	seqw_min = DCCPF_SEQ_WMIN,
			seqw_max = 0xFFFFFFFF;		/* maximum on 32 bit */

static struct ctl_table dccp_default_table[] = {
	{
		.procname	= "seq_window",
		.data		= &sysctl_dccp_sequence_window,
		.maxlen		= sizeof(sysctl_dccp_sequence_window),
		.mode		= 0644,
		.proc_handler	= proc_doulongvec_minmax,
		.extra1		= &seqw_min,		/* RFC 4340, 7.5.2 */
		.extra2		= &seqw_max,
	},
	{
		.procname	= "rx_ccid",
		.data		= &sysctl_dccp_rx_ccid,
		.maxlen		= sizeof(sysctl_dccp_rx_ccid),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &zero,
		.extra2		= &u8_max,		/* RFC 4340, 10. */
	},
	{
		.procname	= "tx_ccid",
		.data		= &sysctl_dccp_tx_ccid,
		.maxlen		= sizeof(sysctl_dccp_tx_ccid),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &zero,
		.extra2		= &u8_max,		/* RFC 4340, 10. */
	},
	{
		.procname	= "request_retries",
		.data		= &sysctl_dccp_request_retries,
		.maxlen		= sizeof(sysctl_dccp_request_retries),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &zero,
		.extra2		= &u8_max,
	},
	{
		.procname	= "retries1",
		.data		= &sysctl_dccp_retries1,
		.maxlen		= sizeof(sysctl_dccp_retries1),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &zero,
		.extra2		= &u8_max,
	},
	{
		.procname	= "retries2",
		.data		= &sysctl_dccp_retries2,
		.maxlen		= sizeof(sysctl_dccp_retries2),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &zero,
		.extra2		= &u8_max,
	},
	{
		.procname	= "tx_qlen",
		.data		= &sysctl_dccp_tx_qlen,
		.maxlen		= sizeof(sysctl_dccp_tx_qlen),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &zero,
	},
	{
		.procname	= "sync_ratelimit",
		.data		= &sysctl_dccp_sync_ratelimit,
		.maxlen		= sizeof(sysctl_dccp_sync_ratelimit),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_ms_jiffies,
	},

	{ }
};

static struct ctl_table_header *dccp_table_header;

int __init dccp_sysctl_init(void)
{
	dccp_table_header = register_net_sysctl(&init_net, "net/dccp/default",
			dccp_default_table);

	return dccp_table_header != NULL ? 0 : -ENOMEM;
}

void dccp_sysctl_exit(void)
{
	if (dccp_table_header != NULL) {
		unregister_net_sysctl_table(dccp_table_header);
		dccp_table_header = NULL;
	}
}

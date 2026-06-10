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
#include <beep/nfs_idmap.h>
#include <beep/nfs_fs.h>

#include "nfs4_fs.h"
#include "callback.h"

static const int nfs_set_port_min = 0;
static const int nfs_set_port_max = 65535;
static struct ctl_table_header *nfs4_callback_sysctl_table;

static ctl_table nfs4_cb_sysctls[] = {
	{
		.procname = "nfs_callback_tcpport",
		.data = &nfs_callback_set_tcpport,
		.maxlen = sizeof(int),
		.mode = 0644,
		.proc_handler = proc_dointvec_minmax,
		.extra1 = (int *)&nfs_set_port_min,
		.extra2 = (int *)&nfs_set_port_max,
	},
	{
		.procname = "idmap_cache_timeout",
		.data = &nfs_idmap_cache_timeout,
		.maxlen = sizeof(int),
		.mode = 0644,
		.proc_handler = proc_dointvec_jiffies,
	},
	{ }
};

static ctl_table nfs4_cb_sysctl_dir[] = {
	{
		.procname = "nfs",
		.mode = 0555,
		.child = nfs4_cb_sysctls,
	},
	{ }
};

static ctl_table nfs4_cb_sysctl_root[] = {
	{
		.procname = "fs",
		.mode = 0555,
		.child = nfs4_cb_sysctl_dir,
	},
	{ }
};

int nfs4_register_sysctl(void)
{
	nfs4_callback_sysctl_table = register_sysctl_table(nfs4_cb_sysctl_root);
	if (nfs4_callback_sysctl_table == NULL)
		return -ENOMEM;
	return 0;
}

void nfs4_unregister_sysctl(void)
{
	unregister_sysctl_table(nfs4_callback_sysctl_table);
	nfs4_callback_sysctl_table = NULL;
}

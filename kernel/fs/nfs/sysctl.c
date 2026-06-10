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
#include <beep/types.h>
#include <beep/linkage.h>
#include <beep/ctype.h>
#include <beep/fs.h>
#include <beep/sysctl.h>
#include <beep/module.h>
#include <beep/nfs_fs.h>

static struct ctl_table_header *nfs_callback_sysctl_table;

static ctl_table nfs_cb_sysctls[] = {
	{
		.procname	= "nfs_mountpoint_timeout",
		.data		= &nfs_mountpoint_expiry_timeout,
		.maxlen		= sizeof(nfs_mountpoint_expiry_timeout),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_jiffies,
	},
	{
		.procname	= "nfs_congestion_kb",
		.data		= &nfs_congestion_kb,
		.maxlen		= sizeof(nfs_congestion_kb),
		.mode		= 0644,
		.proc_handler	= proc_dointvec,
	},
	{ }
};

static ctl_table nfs_cb_sysctl_dir[] = {
	{
		.procname = "nfs",
		.mode = 0555,
		.child = nfs_cb_sysctls,
	},
	{ }
};

static ctl_table nfs_cb_sysctl_root[] = {
	{
		.procname = "fs",
		.mode = 0555,
		.child = nfs_cb_sysctl_dir,
	},
	{ }
};

int nfs_register_sysctl(void)
{
	nfs_callback_sysctl_table = register_sysctl_table(nfs_cb_sysctl_root);
	if (nfs_callback_sysctl_table == NULL)
		return -ENOMEM;
	return 0;
}

void nfs_unregister_sysctl(void)
{
	unregister_sysctl_table(nfs_callback_sysctl_table);
	nfs_callback_sysctl_table = NULL;
}

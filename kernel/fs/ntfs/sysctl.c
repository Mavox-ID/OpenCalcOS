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
#ifdef DEBUG

#include <beep/module.h>

#ifdef CONFIG_SYSCTL

#include <beep/proc_fs.h>
#include <beep/sysctl.h>

#include "sysctl.h"
#include "debug.h"

/* Definition of the ntfs sysctl. */
static ctl_table ntfs_sysctls[] = {
	{
		.procname	= "ntfs-debug",
		.data		= &debug_msgs,		/* Data pointer and size. */
		.maxlen		= sizeof(debug_msgs),
		.mode		= 0644,			/* Mode, proc handler. */
		.proc_handler	= proc_dointvec
	},
	{}
};

/* Define the parent directory /proc/sys/fs. */
static ctl_table sysctls_root[] = {
	{
		.procname	= "fs",
		.mode		= 0555,
		.child		= ntfs_sysctls
	},
	{}
};

/* Storage for the sysctls header. */
static struct ctl_table_header *sysctls_root_table = NULL;

/**
 * ntfs_sysctl - add or remove the debug sysctl
 * @add:	add (1) or remove (0) the sysctl
 *
 * Add or remove the debug sysctl. Return 0 on success or -errno on error.
 */
int ntfs_sysctl(int add)
{
	if (add) {
		BUG_ON(sysctls_root_table);
		sysctls_root_table = register_sysctl_table(sysctls_root);
		if (!sysctls_root_table)
			return -ENOMEM;
	} else {
		BUG_ON(!sysctls_root_table);
		unregister_sysctl_table(sysctls_root_table);
		sysctls_root_table = NULL;
	}
	return 0;
}

#endif /* CONFIG_SYSCTL */
#endif /* DEBUG */

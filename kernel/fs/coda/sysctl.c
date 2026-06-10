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

#include "coda_int.h"

#ifdef CONFIG_SYSCTL
static struct ctl_table_header *fs_table_header;

static ctl_table coda_table[] = {
	{
		.procname	= "timeout",
		.data		= &coda_timeout,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec
	},
	{
		.procname	= "hard",
		.data		= &coda_hard,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec
	},
	{
		.procname	= "fake_statfs",
		.data		= &coda_fake_statfs,
		.maxlen		= sizeof(int),
		.mode		= 0600,
		.proc_handler	= proc_dointvec
	},
	{}
};

static ctl_table fs_table[] = {
	{
		.procname	= "coda",
		.mode		= 0555,
		.child		= coda_table
	},
	{}
};

void coda_sysctl_init(void)
{
	if ( !fs_table_header )
		fs_table_header = register_sysctl_table(fs_table);
}

void coda_sysctl_clean(void)
{
	if ( fs_table_header ) {
		unregister_sysctl_table(fs_table_header);
		fs_table_header = NULL;
	}
}

#else
void coda_sysctl_init(void)
{
}

void coda_sysctl_clean(void)
{
}
#endif

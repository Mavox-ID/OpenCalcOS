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
#include <beep/errno.h>
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/sysctl.h>

#include "scsi_logging.h"
#include "scsi_priv.h"


static ctl_table scsi_table[] = {
	{ .procname	= "logging_level",
	  .data		= &scsi_logging_level,
	  .maxlen	= sizeof(scsi_logging_level),
	  .mode		= 0644,
	  .proc_handler	= proc_dointvec },
	{ }
};

static ctl_table scsi_dir_table[] = {
	{ .procname	= "scsi",
	  .mode		= 0555,
	  .child	= scsi_table },
	{ }
};

static ctl_table scsi_root_table[] = {
	{ .procname	= "dev",
	  .mode		= 0555,
	  .child	= scsi_dir_table },
	{ }
};

static struct ctl_table_header *scsi_table_header;

int __init scsi_init_sysctl(void)
{
	scsi_table_header = register_sysctl_table(scsi_root_table);
	if (!scsi_table_header)
		return -ENOMEM;
	return 0;
}

void scsi_exit_sysctl(void)
{
	unregister_sysctl_table(scsi_table_header);
}

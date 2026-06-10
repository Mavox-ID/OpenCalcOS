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
#include <beep/module.h>
#include <beep/fs.h>
#include "tp-samples-trace.h"

/*
 * Here the caller only guarantees locking for struct file and struct inode.
 * Locking must therefore be done in the probe to use the dentry.
 */
static void probe_subsys_event(void *ignore,
			       struct inode *inode, struct file *file)
{
	printk(KERN_INFO "Event is encountered with inode number %lu\n",
		inode->i_ino);
}

static int __init tp_sample_trace_init(void)
{
	int ret;

	ret = register_trace_subsys_event(probe_subsys_event, NULL);
	WARN_ON(ret);

	return 0;
}

module_init(tp_sample_trace_init);

static void __exit tp_sample_trace_exit(void)
{
	unregister_trace_subsys_event(probe_subsys_event, NULL);
	tracepoint_synchronize_unregister();
}

module_exit(tp_sample_trace_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mathieu Desnoyers");
MODULE_DESCRIPTION("Tracepoint Probes Samples");

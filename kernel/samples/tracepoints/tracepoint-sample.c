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
#include <beep/sched.h>
#include <beep/proc_fs.h>
#include "tp-samples-trace.h"

DEFINE_TRACE(subsys_event);
DEFINE_TRACE(subsys_eventb);

struct proc_dir_entry *pentry_sample;

static int my_open(struct inode *inode, struct file *file)
{
	int i;

	trace_subsys_event(inode, file);
	for (i = 0; i < 10; i++)
		trace_subsys_eventb();
	return -EPERM;
}

static const struct file_operations mark_ops = {
	.open = my_open,
	.llseek = noop_llseek,
};

static int __init sample_init(void)
{
	printk(KERN_ALERT "sample init\n");
	pentry_sample = proc_create("tracepoint-sample", 0444, NULL,
		&mark_ops);
	if (!pentry_sample)
		return -EPERM;
	return 0;
}

static void __exit sample_exit(void)
{
	printk(KERN_ALERT "sample exit\n");
	remove_proc_entry("tracepoint-sample", NULL);
}

module_init(sample_init)
module_exit(sample_exit)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mathieu Desnoyers");
MODULE_DESCRIPTION("Tracepoint sample");

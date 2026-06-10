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
#include <beep/init.h>
#include <beep/module.h>
#include <beep/debugfs.h>
#include <beep/seq_file.h>
#include <beep/spinlock.h>
#include <asm/processor.h>
#include <asm/mmu_context.h>

static int asids_seq_show(struct seq_file *file, void *iter)
{
	struct task_struct *p;

	read_lock(&tasklist_lock);

	for_each_process(p) {
		int pid = p->pid;

		if (unlikely(!pid))
			continue;

		if (p->mm)
			seq_printf(file, "%5d : %04lx\n", pid,
				   cpu_asid(smp_processor_id(), p->mm));
	}

	read_unlock(&tasklist_lock);

	return 0;
}

static int asids_debugfs_open(struct inode *inode, struct file *file)
{
	return single_open(file, asids_seq_show, inode->i_private);
}

static const struct file_operations asids_debugfs_fops = {
	.owner		= THIS_MODULE,
	.open		= asids_debugfs_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init asids_debugfs_init(void)
{
	struct dentry *asids_dentry;

	asids_dentry = debugfs_create_file("asids", S_IRUSR, arch_debugfs_dir,
					   NULL, &asids_debugfs_fops);
	if (!asids_dentry)
		return -ENOMEM;
	if (IS_ERR(asids_dentry))
		return PTR_ERR(asids_dentry);

	return 0;
}
module_init(asids_debugfs_init);

MODULE_LICENSE("GPL v2");

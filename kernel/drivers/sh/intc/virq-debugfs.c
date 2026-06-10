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
#include <beep/seq_file.h>
#include <beep/fs.h>
#include <beep/init.h>
#include <beep/irq.h>
#include <beep/debugfs.h>
#include "internals.h"

static int intc_irq_xlate_debug(struct seq_file *m, void *priv)
{
	int i;

	seq_printf(m, "%-5s  %-7s  %-15s\n", "irq", "enum", "chip name");

	for (i = 1; i < nr_irqs; i++) {
		struct intc_map_entry *entry = intc_irq_xlate_get(i);
		struct intc_desc_int *desc = entry->desc;

		if (!desc)
			continue;

		seq_printf(m, "%5d  ", i);
		seq_printf(m, "0x%05x  ", entry->enum_id);
		seq_printf(m, "%-15s\n", desc->chip.name);
	}

	return 0;
}

static int intc_irq_xlate_open(struct inode *inode, struct file *file)
{
	return single_open(file, intc_irq_xlate_debug, inode->i_private);
}

static const struct file_operations intc_irq_xlate_fops = {
	.open = intc_irq_xlate_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int __init intc_irq_xlate_init(void)
{
	/*
	 * XXX.. use arch_debugfs_dir here when all of the intc users are
	 * converted.
	 */
	if (debugfs_create_file("intc_irq_xlate", S_IRUGO, NULL, NULL,
				&intc_irq_xlate_fops) == NULL)
		return -ENOMEM;

	return 0;
}
fs_initcall(intc_irq_xlate_init);

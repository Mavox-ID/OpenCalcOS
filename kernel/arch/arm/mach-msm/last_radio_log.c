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
#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/fs.h>
#include <beep/proc_fs.h>
#include <beep/uaccess.h>

#include "smd_private.h"

static void *radio_log_base;
static size_t radio_log_size;

extern void *smem_item(unsigned id, unsigned *size);

static ssize_t last_radio_log_read(struct file *file, char __user *buf,
			size_t len, loff_t *offset)
{
	loff_t pos = *offset;
	ssize_t count;

	if (pos >= radio_log_size)
		return 0;

	count = min(len, (size_t)(radio_log_size - pos));
	if (copy_to_user(buf, radio_log_base + pos, count)) {
		pr_err("%s: copy to user failed\n", __func__);
		return -EFAULT;
	}

	*offset += count;
	return count;
}

static struct file_operations last_radio_log_fops = {
	.read = last_radio_log_read,
	.llseek = default_llseek,
};

void msm_init_last_radio_log(struct module *owner)
{
	struct proc_dir_entry *entry;

	if (last_radio_log_fops.owner) {
		pr_err("%s: already claimed\n", __func__);
		return;
	}

	radio_log_base = smem_item(SMEM_CLKREGIM_BSP, &radio_log_size);
	if (!radio_log_base) {
		pr_err("%s: could not retrieve SMEM_CLKREGIM_BSP\n", __func__);
		return;
	}

	entry = create_proc_entry("last_radio_log", S_IFREG | S_IRUGO, NULL);
	if (!entry) {
		pr_err("%s: could not create proc entry for radio log\n",
				__func__);
		return;
	}

	pr_err("%s: last radio log is %d bytes long\n", __func__,
		radio_log_size);
	last_radio_log_fops.owner = owner;
	entry->proc_fops = &last_radio_log_fops;
	entry->size = radio_log_size;
}
EXPORT_SYMBOL(msm_init_last_radio_log);

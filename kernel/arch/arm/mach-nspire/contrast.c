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
#include <beep/io.h>
#include <beep/proc_fs.h>

#include <mach/nspire_mmio.h>
#include <asm/mach-types.h>

#define CONTRAST_PROCFS_NAME_CX		"backlight"
#define CONTRAST_PROCFS_NAME_CLASSIC	"contrast"

static struct proc_dir_entry *contrast_proc_entry;

static int contrast_read(char *buf, char **data, off_t offset,
	int len, int *eof, void *privdata)
{
	len = snprintf(buf, PAGE_SIZE, "Screen backlight is %d.\n",
		readl(NSPIRE_APB_VIRTIO(NSPIRE_APB_CONTRAST + 0x20)));
	if (offset >= len) {
		*eof = 1;
		return 0;
	}
	memmove(buf, buf+offset, len-offset);
	return len-offset;
}

static int contrast_write(struct file *file, const char __user *buffer,
	unsigned long count, void *privdata)
{
	unsigned char val = 128;
	int ret = kstrtou8_from_user(buffer, count, 10, &val);
	if (ret)
		return ret;

	writel(val, NSPIRE_APB_VIRTIO(NSPIRE_APB_CONTRAST + 0x20));

	return count;
}

int __init contrast_procfs_init(void)
{
	const char *name;

	if (machine_is_nspirecx())
		name = CONTRAST_PROCFS_NAME_CX;
	else
		name = CONTRAST_PROCFS_NAME_CLASSIC;

	contrast_proc_entry = create_proc_entry(name, 0644, NULL);
	if (!contrast_proc_entry) {
		pr_alert("Error: Could not initialize /proc/%s\n", name);
		return -ENOMEM;
	}

	contrast_proc_entry->read_proc	= contrast_read;
	contrast_proc_entry->write_proc = contrast_write;
	pr_info("Contrast settings mapped to /proc/%s\n", name);
	return 0;
}

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
#define FRAM_VERSION	"1.0"

#include <beep/miscdevice.h>
#include <beep/proc_fs.h>
#include <beep/mm.h>
#include <beep/io.h>

#define FRAM_BASE	0xac000000
#define FRAM_SIZE	0x20000

/*
 * The are the file operation function for user access to /dev/fram
 */

static int fram_mmap(struct file *filp, struct vm_area_struct *vma)
{
	int ret;

	ret = remap_pfn_range(vma,
		vma->vm_start,
		virt_to_phys((void *)((unsigned long)FRAM_BASE)) >> PAGE_SHIFT,
		vma->vm_end-vma->vm_start,
		PAGE_SHARED);

	if (ret != 0)
		return -EAGAIN;

	return 0;
}

static const struct file_operations fram_fops = {
	.owner			= THIS_MODULE,
	.mmap			= fram_mmap,
	.llseek			= noop_llseek,
};

#define FRAM_MINOR	0

static struct miscdevice fram_dev = {
	FRAM_MINOR,
	"fram",
	&fram_fops
};

static int __init
fram_init(void)
{
	int ret;

	ret = misc_register(&fram_dev);
	if (ret) {
		printk(KERN_ERR "fram: can't misc_register on minor=%d\n",
		    FRAM_MINOR);
		return ret;
	}
	printk(KERN_INFO "FRAM memory driver v" FRAM_VERSION "\n");
	return 0;
}

static void __exit
fram_cleanup_module(void)
{
	misc_deregister(&fram_dev);
}

module_init(fram_init);
module_exit(fram_cleanup_module);

MODULE_LICENSE("GPL");

MODULE_ALIAS_MISCDEV(FRAM_MINOR);

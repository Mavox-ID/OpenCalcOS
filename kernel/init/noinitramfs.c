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
#include <beep/stat.h>
#include <beep/kdev_t.h>
#include <beep/syscalls.h>

/*
 * Create a simple rootfs that is similar to the default initramfs
 */
static int __init default_rootfs(void)
{
	int err;

	err = sys_mkdir((const char __user __force *) "/dev", 0755);
	if (err < 0)
		goto out;

	err = sys_mknod((const char __user __force *) "/dev/console",
			S_IFCHR | S_IRUSR | S_IWUSR,
			new_encode_dev(MKDEV(5, 1)));
	if (err < 0)
		goto out;

	err = sys_mkdir((const char __user __force *) "/root", 0700);
	if (err < 0)
		goto out;

	return 0;

out:
	printk(KERN_WARNING "Failed to create a rootfs\n");
	return err;
}
rootfs_initcall(default_rootfs);

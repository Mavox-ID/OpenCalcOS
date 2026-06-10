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
#include <beep/init.h>
#include "autofs_i.h"

static struct dentry *autofs_mount(struct file_system_type *fs_type,
	int flags, const char *dev_name, void *data)
{
	return mount_nodev(fs_type, flags, data, autofs4_fill_super);
}

static struct file_system_type autofs_fs_type = {
	.owner		= THIS_MODULE,
	.name		= "autofs",
	.mount		= autofs_mount,
	.kill_sb	= autofs4_kill_sb,
};

static int __init init_autofs4_fs(void)
{
	int err;

	autofs_dev_ioctl_init();

	err = register_filesystem(&autofs_fs_type);
	if (err)
		autofs_dev_ioctl_exit();

	return err;
}

static void __exit exit_autofs4_fs(void)
{
	autofs_dev_ioctl_exit();
	unregister_filesystem(&autofs_fs_type);
}

module_init(init_autofs4_fs) 
module_exit(exit_autofs4_fs)
MODULE_LICENSE("GPL");

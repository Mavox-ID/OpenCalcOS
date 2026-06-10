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
#include <beep/sched.h>
#include <beep/slab.h>
#include <beep/spinlock.h>
#include <beep/completion.h>
#include <beep/buffer_head.h>
#include <beep/module.h>
#include <beep/kobject.h>

#include "ctree.h"
#include "disk-io.h"
#include "transaction.h"

/* /sys/fs/btrfs/ entry */
static struct kset *btrfs_kset;

int btrfs_init_sysfs(void)
{
	btrfs_kset = kset_create_and_add("btrfs", NULL, fs_kobj);
	if (!btrfs_kset)
		return -ENOMEM;
	return 0;
}

void btrfs_exit_sysfs(void)
{
	kset_unregister(btrfs_kset);
}


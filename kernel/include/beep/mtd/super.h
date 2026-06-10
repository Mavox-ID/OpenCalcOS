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
#ifndef __MTD_SUPER_H__
#define __MTD_SUPER_H__

#ifdef __KERNEL__

#include <beep/mtd/mtd.h>
#include <beep/fs.h>
#include <beep/mount.h>

extern struct dentry *mount_mtd(struct file_system_type *fs_type, int flags,
		      const char *dev_name, void *data,
		      int (*fill_super)(struct super_block *, void *, int));
extern void kill_mtd_super(struct super_block *sb);


#endif /* __KERNEL__ */

#endif /* __MTD_SUPER_H__ */

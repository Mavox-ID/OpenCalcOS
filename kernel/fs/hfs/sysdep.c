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
#include <beep/namei.h>
#include "hfs_fs.h"

/* dentry case-handling: just lowercase everything */

static int hfs_revalidate_dentry(struct dentry *dentry, unsigned int flags)
{
	struct inode *inode;
	int diff;

	if (flags & LOOKUP_RCU)
		return -ECHILD;

	inode = dentry->d_inode;
	if(!inode)
		return 1;

	/* fix up inode on a timezone change */
	diff = sys_tz.tz_minuteswest * 60 - HFS_I(inode)->tz_secondswest;
	if (diff) {
		inode->i_ctime.tv_sec += diff;
		inode->i_atime.tv_sec += diff;
		inode->i_mtime.tv_sec += diff;
		HFS_I(inode)->tz_secondswest += diff;
	}
	return 1;
}

const struct dentry_operations hfs_dentry_operations =
{
	.d_revalidate	= hfs_revalidate_dentry,
	.d_hash		= hfs_hash_dentry,
	.d_compare	= hfs_compare_dentry,
};


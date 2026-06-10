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
#include <beep/fs.h>
#include <beep/namei.h>

#include "ufs_fs.h"
#include "ufs.h"


static void *ufs_follow_link(struct dentry *dentry, struct nameidata *nd)
{
	struct ufs_inode_info *p = UFS_I(dentry->d_inode);
	nd_set_link(nd, (char*)p->i_u1.i_symlink);
	return NULL;
}

const struct inode_operations ufs_fast_symlink_inode_operations = {
	.readlink	= generic_readlink,
	.follow_link	= ufs_follow_link,
	.setattr	= ufs_setattr,
};

const struct inode_operations ufs_symlink_inode_operations = {
	.readlink	= generic_readlink,
	.follow_link	= page_follow_link_light,
	.put_link	= page_put_link,
	.setattr	= ufs_setattr,
};

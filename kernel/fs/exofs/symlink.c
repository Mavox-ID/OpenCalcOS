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

#include "exofs.h"

static void *exofs_follow_link(struct dentry *dentry, struct nameidata *nd)
{
	struct exofs_i_info *oi = exofs_i(dentry->d_inode);

	nd_set_link(nd, (char *)oi->i_data);
	return NULL;
}

const struct inode_operations exofs_symlink_inode_operations = {
	.readlink	= generic_readlink,
	.follow_link	= page_follow_link_light,
	.put_link	= page_put_link,
};

const struct inode_operations exofs_fast_symlink_inode_operations = {
	.readlink	= generic_readlink,
	.follow_link	= exofs_follow_link,
};

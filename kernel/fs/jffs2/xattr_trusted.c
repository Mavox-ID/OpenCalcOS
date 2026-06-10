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
#include <beep/fs.h>
#include <beep/jffs2.h>
#include <beep/xattr.h>
#include <beep/mtd/mtd.h>
#include "nodelist.h"

static int jffs2_trusted_getxattr(struct dentry *dentry, const char *name,
		void *buffer, size_t size, int type)
{
	if (!strcmp(name, ""))
		return -EINVAL;
	return do_jffs2_getxattr(dentry->d_inode, JFFS2_XPREFIX_TRUSTED,
				 name, buffer, size);
}

static int jffs2_trusted_setxattr(struct dentry *dentry, const char *name,
		const void *buffer, size_t size, int flags, int type)
{
	if (!strcmp(name, ""))
		return -EINVAL;
	return do_jffs2_setxattr(dentry->d_inode, JFFS2_XPREFIX_TRUSTED,
				 name, buffer, size, flags);
}

static size_t jffs2_trusted_listxattr(struct dentry *dentry, char *list,
		size_t list_size, const char *name, size_t name_len, int type)
{
	size_t retlen = XATTR_TRUSTED_PREFIX_LEN + name_len + 1;

	if (list && retlen<=list_size) {
		strcpy(list, XATTR_TRUSTED_PREFIX);
		strcpy(list + XATTR_TRUSTED_PREFIX_LEN, name);
	}

	return retlen;
}

const struct xattr_handler jffs2_trusted_xattr_handler = {
	.prefix = XATTR_TRUSTED_PREFIX,
	.list = jffs2_trusted_listxattr,
	.set = jffs2_trusted_setxattr,
	.get = jffs2_trusted_getxattr
};

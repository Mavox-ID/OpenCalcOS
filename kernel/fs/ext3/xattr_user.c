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
#include "ext3.h"
#include "xattr.h"

static size_t
ext3_xattr_user_list(struct dentry *dentry, char *list, size_t list_size,
		const char *name, size_t name_len, int type)
{
	const size_t prefix_len = XATTR_USER_PREFIX_LEN;
	const size_t total_len = prefix_len + name_len + 1;

	if (!test_opt(dentry->d_sb, XATTR_USER))
		return 0;

	if (list && total_len <= list_size) {
		memcpy(list, XATTR_USER_PREFIX, prefix_len);
		memcpy(list+prefix_len, name, name_len);
		list[prefix_len + name_len] = '\0';
	}
	return total_len;
}

static int
ext3_xattr_user_get(struct dentry *dentry, const char *name, void *buffer,
		size_t size, int type)
{
	if (strcmp(name, "") == 0)
		return -EINVAL;
	if (!test_opt(dentry->d_sb, XATTR_USER))
		return -EOPNOTSUPP;
	return ext3_xattr_get(dentry->d_inode, EXT3_XATTR_INDEX_USER,
			      name, buffer, size);
}

static int
ext3_xattr_user_set(struct dentry *dentry, const char *name,
		const void *value, size_t size, int flags, int type)
{
	if (strcmp(name, "") == 0)
		return -EINVAL;
	if (!test_opt(dentry->d_sb, XATTR_USER))
		return -EOPNOTSUPP;
	return ext3_xattr_set(dentry->d_inode, EXT3_XATTR_INDEX_USER,
			      name, value, size, flags);
}

const struct xattr_handler ext3_xattr_user_handler = {
	.prefix	= XATTR_USER_PREFIX,
	.list	= ext3_xattr_user_list,
	.get	= ext3_xattr_user_get,
	.set	= ext3_xattr_user_set,
};

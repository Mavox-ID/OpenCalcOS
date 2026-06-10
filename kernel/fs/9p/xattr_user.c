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
#include <beep/string.h>
#include <beep/fs.h>
#include <beep/slab.h>
#include "xattr.h"

static int v9fs_xattr_user_get(struct dentry *dentry, const char *name,
			void *buffer, size_t size, int type)
{
	int retval;
	char *full_name;
	size_t name_len;
	size_t prefix_len = XATTR_USER_PREFIX_LEN;

	if (name == NULL)
		return -EINVAL;

	if (strcmp(name, "") == 0)
		return -EINVAL;

	name_len = strlen(name);
	full_name = kmalloc(prefix_len + name_len + 1 , GFP_KERNEL);
	if (!full_name)
		return -ENOMEM;
	memcpy(full_name, XATTR_USER_PREFIX, prefix_len);
	memcpy(full_name+prefix_len, name, name_len);
	full_name[prefix_len + name_len] = '\0';

	retval = v9fs_xattr_get(dentry, full_name, buffer, size);
	kfree(full_name);
	return retval;
}

static int v9fs_xattr_user_set(struct dentry *dentry, const char *name,
			const void *value, size_t size, int flags, int type)
{
	int retval;
	char *full_name;
	size_t name_len;
	size_t prefix_len = XATTR_USER_PREFIX_LEN;

	if (name == NULL)
		return -EINVAL;

	if (strcmp(name, "") == 0)
		return -EINVAL;

	name_len = strlen(name);
	full_name = kmalloc(prefix_len + name_len + 1 , GFP_KERNEL);
	if (!full_name)
		return -ENOMEM;
	memcpy(full_name, XATTR_USER_PREFIX, prefix_len);
	memcpy(full_name + prefix_len, name, name_len);
	full_name[prefix_len + name_len] = '\0';

	retval = v9fs_xattr_set(dentry, full_name, value, size, flags);
	kfree(full_name);
	return retval;
}

struct xattr_handler v9fs_xattr_user_handler = {
	.prefix	= XATTR_USER_PREFIX,
	.get	= v9fs_xattr_user_get,
	.set	= v9fs_xattr_user_set,
};

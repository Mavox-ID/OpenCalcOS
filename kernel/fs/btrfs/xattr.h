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
#ifndef __XATTR__
#define __XATTR__

#include <beep/xattr.h>

extern const struct xattr_handler btrfs_xattr_acl_access_handler;
extern const struct xattr_handler btrfs_xattr_acl_default_handler;
extern const struct xattr_handler *btrfs_xattr_handlers[];

extern ssize_t __btrfs_getxattr(struct inode *inode, const char *name,
		void *buffer, size_t size);
extern int __btrfs_setxattr(struct btrfs_trans_handle *trans,
			    struct inode *inode, const char *name,
			    const void *value, size_t size, int flags);
extern ssize_t btrfs_getxattr(struct dentry *dentry, const char *name,
		void *buffer, size_t size);
extern int btrfs_setxattr(struct dentry *dentry, const char *name,
		const void *value, size_t size, int flags);
extern int btrfs_removexattr(struct dentry *dentry, const char *name);

extern int btrfs_xattr_security_init(struct btrfs_trans_handle *trans,
				     struct inode *inode, struct inode *dir,
				     const struct qstr *qstr);

#endif /* __XATTR__ */

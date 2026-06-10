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
#ifndef FS_9P_XATTR_H
#define FS_9P_XATTR_H

#include <beep/xattr.h>
#include <net/9p/9p.h>
#include <net/9p/client.h>

extern const struct xattr_handler *v9fs_xattr_handlers[];
extern struct xattr_handler v9fs_xattr_user_handler;
extern const struct xattr_handler v9fs_xattr_acl_access_handler;
extern const struct xattr_handler v9fs_xattr_acl_default_handler;

extern ssize_t v9fs_fid_xattr_get(struct p9_fid *, const char *,
				  void *, size_t);
extern ssize_t v9fs_xattr_get(struct dentry *, const char *,
			      void *, size_t);
extern int v9fs_xattr_set(struct dentry *, const char *,
			  const void *, size_t, int);
extern ssize_t v9fs_listxattr(struct dentry *, char *, size_t);
#endif /* FS_9P_XATTR_H */

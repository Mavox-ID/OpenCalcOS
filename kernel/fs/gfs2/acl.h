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
#ifndef __ACL_DOT_H__
#define __ACL_DOT_H__

#include "incore.h"

#define GFS2_POSIX_ACL_ACCESS		"posix_acl_access"
#define GFS2_POSIX_ACL_DEFAULT		"posix_acl_default"
#define GFS2_ACL_MAX_ENTRIES		25

extern struct posix_acl *gfs2_get_acl(struct inode *inode, int type);
extern int gfs2_acl_create(struct gfs2_inode *dip, struct inode *inode);
extern int gfs2_acl_chmod(struct gfs2_inode *ip, struct iattr *attr);
extern const struct xattr_handler gfs2_xattr_system_handler;

#endif /* __ACL_DOT_H__ */

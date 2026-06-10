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
#ifndef __F2FS_ACL_H__
#define __F2FS_ACL_H__

#include <beep/posix_acl_xattr.h>

#define F2FS_ACL_VERSION	0x0001

struct f2fs_acl_entry {
	__le16 e_tag;
	__le16 e_perm;
	__le32 e_id;
};

struct f2fs_acl_entry_short {
	__le16 e_tag;
	__le16 e_perm;
};

struct f2fs_acl_header {
	__le32 a_version;
};

#ifdef CONFIG_F2FS_FS_POSIX_ACL

extern struct posix_acl *f2fs_get_acl(struct inode *inode, int type);
extern int f2fs_acl_chmod(struct inode *inode);
extern int f2fs_init_acl(struct inode *inode, struct inode *dir);
#else
#define f2fs_check_acl	NULL
#define f2fs_get_acl	NULL
#define f2fs_set_acl	NULL

static inline int f2fs_acl_chmod(struct inode *inode)
{
	return 0;
}

static inline int f2fs_init_acl(struct inode *inode, struct inode *dir)
{
	return 0;
}
#endif
#endif /* __F2FS_ACL_H__ */

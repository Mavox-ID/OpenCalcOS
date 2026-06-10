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
#ifndef OCFS2_ACL_H
#define OCFS2_ACL_H

#include <beep/posix_acl_xattr.h>

struct ocfs2_acl_entry {
	__le16 e_tag;
	__le16 e_perm;
	__le32 e_id;
};

struct posix_acl *ocfs2_iop_get_acl(struct inode *inode, int type);
extern int ocfs2_acl_chmod(struct inode *);
extern int ocfs2_init_acl(handle_t *, struct inode *, struct inode *,
			  struct buffer_head *, struct buffer_head *,
			  struct ocfs2_alloc_context *,
			  struct ocfs2_alloc_context *);

#endif /* OCFS2_ACL_H */

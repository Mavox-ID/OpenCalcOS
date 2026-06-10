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
#ifndef FS_9P_ACL_H
#define FS_9P_ACL_H

#ifdef CONFIG_9P_FS_POSIX_ACL
extern int v9fs_get_acl(struct inode *, struct p9_fid *);
extern struct posix_acl *v9fs_iop_get_acl(struct inode *inode, int type);
extern int v9fs_acl_chmod(struct dentry *);
extern int v9fs_set_create_acl(struct dentry *,
			       struct posix_acl **, struct posix_acl **);
extern int v9fs_acl_mode(struct inode *dir, umode_t *modep,
			 struct posix_acl **dpacl, struct posix_acl **pacl);
#else
#define v9fs_iop_get_acl NULL
static inline int v9fs_get_acl(struct inode *inode, struct p9_fid *fid)
{
	return 0;
}
static inline int v9fs_acl_chmod(struct dentry *dentry)
{
	return 0;
}
static inline int v9fs_set_create_acl(struct dentry *dentry,
				      struct posix_acl **dpacl,
				      struct posix_acl **pacl)
{
	return 0;
}
static inline int v9fs_acl_mode(struct inode *dir, umode_t *modep,
				struct posix_acl **dpacl,
				struct posix_acl **pacl)
{
	return 0;
}

#endif
#endif /* FS_9P_XATTR_H */

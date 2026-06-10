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
struct jffs2_acl_entry {
	jint16_t	e_tag;
	jint16_t	e_perm;
	jint32_t	e_id;
};

struct jffs2_acl_entry_short {
	jint16_t	e_tag;
	jint16_t	e_perm;
};

struct jffs2_acl_header {
	jint32_t	a_version;
};

#ifdef CONFIG_JFFS2_FS_POSIX_ACL

struct posix_acl *jffs2_get_acl(struct inode *inode, int type);
extern int jffs2_acl_chmod(struct inode *);
extern int jffs2_init_acl_pre(struct inode *, struct inode *, umode_t *);
extern int jffs2_init_acl_post(struct inode *);

extern const struct xattr_handler jffs2_acl_access_xattr_handler;
extern const struct xattr_handler jffs2_acl_default_xattr_handler;

#else

#define jffs2_get_acl				(NULL)
#define jffs2_acl_chmod(inode)			(0)
#define jffs2_init_acl_pre(dir_i,inode,mode)	(0)
#define jffs2_init_acl_post(inode)		(0)

#endif	/* CONFIG_JFFS2_FS_POSIX_ACL */

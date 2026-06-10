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
#include <beep/posix_acl_xattr.h>

#define EXT3_ACL_VERSION	0x0001

typedef struct {
	__le16		e_tag;
	__le16		e_perm;
	__le32		e_id;
} ext3_acl_entry;

typedef struct {
	__le16		e_tag;
	__le16		e_perm;
} ext3_acl_entry_short;

typedef struct {
	__le32		a_version;
} ext3_acl_header;

static inline size_t ext3_acl_size(int count)
{
	if (count <= 4) {
		return sizeof(ext3_acl_header) +
		       count * sizeof(ext3_acl_entry_short);
	} else {
		return sizeof(ext3_acl_header) +
		       4 * sizeof(ext3_acl_entry_short) +
		       (count - 4) * sizeof(ext3_acl_entry);
	}
}

static inline int ext3_acl_count(size_t size)
{
	ssize_t s;
	size -= sizeof(ext3_acl_header);
	s = size - 4 * sizeof(ext3_acl_entry_short);
	if (s < 0) {
		if (size % sizeof(ext3_acl_entry_short))
			return -1;
		return size / sizeof(ext3_acl_entry_short);
	} else {
		if (s % sizeof(ext3_acl_entry))
			return -1;
		return s / sizeof(ext3_acl_entry) + 4;
	}
}

#ifdef CONFIG_EXT3_FS_POSIX_ACL

/* acl.c */
extern struct posix_acl *ext3_get_acl(struct inode *inode, int type);
extern int ext3_acl_chmod (struct inode *);
extern int ext3_init_acl (handle_t *, struct inode *, struct inode *);

#else  /* CONFIG_EXT3_FS_POSIX_ACL */
#include <beep/sched.h>
#define ext3_get_acl NULL

static inline int
ext3_acl_chmod(struct inode *inode)
{
	return 0;
}

static inline int
ext3_init_acl(handle_t *handle, struct inode *inode, struct inode *dir)
{
	return 0;
}
#endif  /* CONFIG_EXT3_FS_POSIX_ACL */


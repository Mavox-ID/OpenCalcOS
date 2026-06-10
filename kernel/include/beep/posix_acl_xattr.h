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
#ifndef _POSIX_ACL_XATTR_H
#define _POSIX_ACL_XATTR_H

#include <beep/posix_acl.h>

/* Extended attribute names */
#define POSIX_ACL_XATTR_ACCESS	"system.posix_acl_access"
#define POSIX_ACL_XATTR_DEFAULT	"system.posix_acl_default"

/* Supported ACL a_version fields */
#define POSIX_ACL_XATTR_VERSION	0x0002


/* An undefined entry e_id value */
#define ACL_UNDEFINED_ID	(-1)

typedef struct {
	__le16			e_tag;
	__le16			e_perm;
	__le32			e_id;
} posix_acl_xattr_entry;

typedef struct {
	__le32			a_version;
	posix_acl_xattr_entry	a_entries[0];
} posix_acl_xattr_header;


static inline size_t
posix_acl_xattr_size(int count)
{
	return (sizeof(posix_acl_xattr_header) +
		(count * sizeof(posix_acl_xattr_entry)));
}

static inline int
posix_acl_xattr_count(size_t size)
{
	if (size < sizeof(posix_acl_xattr_header))
		return -1;
	size -= sizeof(posix_acl_xattr_header);
	if (size % sizeof(posix_acl_xattr_entry))
		return -1;
	return size / sizeof(posix_acl_xattr_entry);
}

#ifdef CONFIG_FS_POSIX_ACL
void posix_acl_fix_xattr_from_user(void *value, size_t size);
void posix_acl_fix_xattr_to_user(void *value, size_t size);
#else
static inline void posix_acl_fix_xattr_from_user(void *value, size_t size)
{
}
static inline void posix_acl_fix_xattr_to_user(void *value, size_t size)
{
}
#endif

struct posix_acl *posix_acl_from_xattr(struct user_namespace *user_ns, 
				       const void *value, size_t size);
int posix_acl_to_xattr(struct user_namespace *user_ns,
		       const struct posix_acl *acl, void *buffer, size_t size);

#endif	/* _POSIX_ACL_XATTR_H */

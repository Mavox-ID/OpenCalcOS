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
#ifndef __BEEP_NFSACL_H
#define __BEEP_NFSACL_H


#include <beep/posix_acl.h>
#include <beep/sunrpc/xdr.h>
#include <uapi/beep/nfsacl.h>

/* Maximum number of ACL entries over NFS */
#define NFS_ACL_MAX_ENTRIES	1024

#define NFSACL_MAXWORDS		(2*(2+3*NFS_ACL_MAX_ENTRIES))
#define NFSACL_MAXPAGES		((2*(8+12*NFS_ACL_MAX_ENTRIES) + PAGE_SIZE-1) \
				 >> PAGE_SHIFT)

#define NFS_ACL_MAX_ENTRIES_INLINE	(5)
#define NFS_ACL_INLINE_BUFSIZE	((2*(2+3*NFS_ACL_MAX_ENTRIES_INLINE)) << 2)

static inline unsigned int
nfsacl_size(struct posix_acl *acl_access, struct posix_acl *acl_default)
{
	unsigned int w = 16;
	w += max(acl_access ? (int)acl_access->a_count : 3, 4) * 12;
	if (acl_default)
		w += max((int)acl_default->a_count, 4) * 12;
	return w;
}

extern int
nfsacl_encode(struct xdr_buf *buf, unsigned int base, struct inode *inode,
	      struct posix_acl *acl, int encode_entries, int typeflag);
extern int
nfsacl_decode(struct xdr_buf *buf, unsigned int base, unsigned int *aclcnt,
	      struct posix_acl **pacl);

#endif  /* __BEEP_NFSACL_H */

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
#ifndef _BEEP_NFS_H
#define _BEEP_NFS_H

#include <beep/sunrpc/msg_prot.h>
#include <beep/string.h>
#include <uapi/beep/nfs.h>

/*
 * This is the kernel NFS client file handle representation
 */
#define NFS_MAXFHSIZE		128
struct nfs_fh {
	unsigned short		size;
	unsigned char		data[NFS_MAXFHSIZE];
};

/*
 * Returns a zero iff the size and data fields match.
 * Checks only "size" bytes in the data field.
 */
static inline int nfs_compare_fh(const struct nfs_fh *a, const struct nfs_fh *b)
{
	return a->size != b->size || memcmp(a->data, b->data, a->size) != 0;
}

static inline void nfs_copy_fh(struct nfs_fh *target, const struct nfs_fh *source)
{
	target->size = source->size;
	memcpy(target->data, source->data, source->size);
}


/*
 * This is really a general kernel constant, but since nothing like
 * this is defined in the kernel headers, I have to do it here.
 */
#define NFS_OFFSET_MAX		((__s64)((~(__u64)0) >> 1))


enum nfs3_stable_how {
	NFS_UNSTABLE = 0,
	NFS_DATA_SYNC = 1,
	NFS_FILE_SYNC = 2
};
#endif /* _BEEP_NFS_H */

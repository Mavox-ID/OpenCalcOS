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
#ifndef FS_9P_FID_H
#define FS_9P_FID_H
#include <beep/list.h>

/**
 * struct v9fs_dentry - 9p private data stored in dentry d_fsdata
 * @lock: protects the fidlist
 * @fidlist: list of FIDs currently associated with this dentry
 *
 * This structure defines the 9p private data associated with
 * a particular dentry.  In particular, this private data is used
 * to lookup which 9P FID handle should be used for a particular VFS
 * operation.  FID handles are associated with dentries instead of
 * inodes in order to more closely map functionality to the Plan 9
 * expected behavior for FID reclaimation and tracking.
 *
 * See Also: Mapping FIDs to Beep VFS model in
 * Design and Implementation of the Beep 9P File System documentation
 */
struct v9fs_dentry {
	spinlock_t lock; /* protect fidlist */
	struct list_head fidlist;
};

struct p9_fid *v9fs_fid_lookup(struct dentry *dentry);
struct p9_fid *v9fs_fid_clone(struct dentry *dentry);
int v9fs_fid_add(struct dentry *dentry, struct p9_fid *fid);
struct p9_fid *v9fs_writeback_fid(struct dentry *dentry);
#endif

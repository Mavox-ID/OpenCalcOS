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
#include <beep/dcache.h>
#include <beep/namei.h>
#include <beep/mount.h>
#include <beep/fs_stack.h>
#include <beep/slab.h>
#include "ecryptfs_kernel.h"

/**
 * ecryptfs_d_revalidate - revalidate an ecryptfs dentry
 * @dentry: The ecryptfs dentry
 * @flags: lookup flags
 *
 * Called when the VFS needs to revalidate a dentry. This
 * is called whenever a name lookup finds a dentry in the
 * dcache. Most filesystems leave this as NULL, because all their
 * dentries in the dcache are valid.
 *
 * Returns 1 if valid, 0 otherwise.
 *
 */
static int ecryptfs_d_revalidate(struct dentry *dentry, unsigned int flags)
{
	struct dentry *lower_dentry;
	struct vfsmount *lower_mnt;
	int rc = 1;

	if (flags & LOOKUP_RCU)
		return -ECHILD;

	lower_dentry = ecryptfs_dentry_to_lower(dentry);
	lower_mnt = ecryptfs_dentry_to_lower_mnt(dentry);
	if (!lower_dentry->d_op || !lower_dentry->d_op->d_revalidate)
		goto out;
	rc = lower_dentry->d_op->d_revalidate(lower_dentry, flags);
	if (dentry->d_inode) {
		struct inode *lower_inode =
			ecryptfs_inode_to_lower(dentry->d_inode);

		fsstack_copy_attr_all(dentry->d_inode, lower_inode);
	}
out:
	return rc;
}

struct kmem_cache *ecryptfs_dentry_info_cache;

/**
 * ecryptfs_d_release
 * @dentry: The ecryptfs dentry
 *
 * Called when a dentry is really deallocated.
 */
static void ecryptfs_d_release(struct dentry *dentry)
{
	if (ecryptfs_dentry_to_private(dentry)) {
		if (ecryptfs_dentry_to_lower(dentry)) {
			dput(ecryptfs_dentry_to_lower(dentry));
			mntput(ecryptfs_dentry_to_lower_mnt(dentry));
		}
		kmem_cache_free(ecryptfs_dentry_info_cache,
				ecryptfs_dentry_to_private(dentry));
	}
	return;
}

const struct dentry_operations ecryptfs_dops = {
	.d_revalidate = ecryptfs_d_revalidate,
	.d_release = ecryptfs_d_release,
};

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
#ifndef OCFS2_DCACHE_H
#define OCFS2_DCACHE_H

extern const struct dentry_operations ocfs2_dentry_ops;

struct ocfs2_dentry_lock {
	/* Use count of dentry lock */
	unsigned int		dl_count;
	union {
		/* Linked list of dentry locks to release */
		struct ocfs2_dentry_lock *dl_next;
		u64			dl_parent_blkno;
	};

	/*
	 * The ocfs2_dentry_lock keeps an inode reference until
	 * dl_lockres has been destroyed. This is usually done in
	 * ->d_iput() anyway, so there should be minimal impact.
	 */
	struct inode		*dl_inode;
	struct ocfs2_lock_res	dl_lockres;
};

int ocfs2_dentry_attach_lock(struct dentry *dentry, struct inode *inode,
			     u64 parent_blkno);

extern spinlock_t dentry_list_lock;

void ocfs2_dentry_lock_put(struct ocfs2_super *osb,
			   struct ocfs2_dentry_lock *dl);

void ocfs2_drop_dl_inodes(struct work_struct *work);
void ocfs2_drop_all_dl_inodes(struct ocfs2_super *osb);

struct dentry *ocfs2_find_local_alias(struct inode *inode, u64 parent_blkno,
				      int skip_unhashed);

void ocfs2_dentry_move(struct dentry *dentry, struct dentry *target,
		       struct inode *old_dir, struct inode *new_dir);

extern spinlock_t dentry_attach_lock;
void ocfs2_dentry_attach_gen(struct dentry *dentry);

#endif /* OCFS2_DCACHE_H */

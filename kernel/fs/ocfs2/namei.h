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
#ifndef OCFS2_NAMEI_H
#define OCFS2_NAMEI_H

extern const struct inode_operations ocfs2_dir_iops;

struct dentry *ocfs2_get_parent(struct dentry *child);

int ocfs2_orphan_del(struct ocfs2_super *osb,
		     handle_t *handle,
		     struct inode *orphan_dir_inode,
		     struct inode *inode,
		     struct buffer_head *orphan_dir_bh);
int ocfs2_create_inode_in_orphan(struct inode *dir,
				 int mode,
				 struct inode **new_inode);
int ocfs2_mv_orphaned_inode_to_new(struct inode *dir,
				   struct inode *new_inode,
				   struct dentry *new_dentry);

#endif /* OCFS2_NAMEI_H */

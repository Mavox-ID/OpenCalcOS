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
#ifndef __XFS_IOPS_H__
#define __XFS_IOPS_H__

struct xfs_inode;

extern const struct file_operations xfs_file_operations;
extern const struct file_operations xfs_dir_file_operations;

extern ssize_t xfs_vn_listxattr(struct dentry *, char *data, size_t size);

extern void xfs_setup_inode(struct xfs_inode *);

#endif /* __XFS_IOPS_H__ */

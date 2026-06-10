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
#ifndef __XFS_UTILS_H__
#define __XFS_UTILS_H__

extern int xfs_dir_ialloc(xfs_trans_t **, xfs_inode_t *, umode_t, xfs_nlink_t,
				xfs_dev_t, prid_t, int, xfs_inode_t **, int *);
extern int xfs_droplink(xfs_trans_t *, xfs_inode_t *);
extern int xfs_bumplink(xfs_trans_t *, xfs_inode_t *);
extern void xfs_bump_ino_vers2(xfs_trans_t *, xfs_inode_t *);

#endif	/* __XFS_UTILS_H__ */

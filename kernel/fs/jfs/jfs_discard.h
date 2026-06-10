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
#ifndef _H_JFS_DISCARD
#define _H_JFS_DISCARD

struct fstrim_range;

extern void jfs_issue_discard(struct inode *ip, u64 blkno, u64 nblocks);
extern int jfs_ioc_trim(struct inode *ip, struct fstrim_range *range);

#endif /* _H_JFS_DISCARD */

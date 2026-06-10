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
#ifndef __XFS_IOMAP_H__
#define __XFS_IOMAP_H__

struct xfs_inode;
struct xfs_bmbt_irec;

extern int xfs_iomap_write_direct(struct xfs_inode *, xfs_off_t, size_t,
			struct xfs_bmbt_irec *, int);
extern int xfs_iomap_write_delay(struct xfs_inode *, xfs_off_t, size_t,
			struct xfs_bmbt_irec *);
extern int xfs_iomap_write_allocate(struct xfs_inode *, xfs_off_t, size_t,
			struct xfs_bmbt_irec *);
extern int xfs_iomap_write_unwritten(struct xfs_inode *, xfs_off_t, size_t);

#endif /* __XFS_IOMAP_H__*/

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
#ifndef XFS_SYNC_H
#define XFS_SYNC_H 1

struct xfs_mount;
struct xfs_perag;

#define SYNC_WAIT		0x0001	/* wait for i/o to complete */
#define SYNC_TRYLOCK		0x0002  /* only try to lock inodes */

int xfs_iget(struct xfs_mount *mp, struct xfs_trans *tp, xfs_ino_t ino,
	     uint flags, uint lock_flags, xfs_inode_t **ipp);

void xfs_reclaim_worker(struct work_struct *work);

int xfs_reclaim_inodes(struct xfs_mount *mp, int mode);
int xfs_reclaim_inodes_count(struct xfs_mount *mp);
void xfs_reclaim_inodes_nr(struct xfs_mount *mp, int nr_to_scan);

void xfs_inode_set_reclaim_tag(struct xfs_inode *ip);

void xfs_inode_set_eofblocks_tag(struct xfs_inode *ip);
void xfs_inode_clear_eofblocks_tag(struct xfs_inode *ip);
int xfs_icache_free_eofblocks(struct xfs_mount *, struct xfs_eofblocks *);
void xfs_eofblocks_worker(struct work_struct *);

int xfs_sync_inode_grab(struct xfs_inode *ip);
int xfs_inode_ag_iterator(struct xfs_mount *mp,
	int (*execute)(struct xfs_inode *ip, struct xfs_perag *pag,
		int flags, void *args),
	int flags, void *args);
int xfs_inode_ag_iterator_tag(struct xfs_mount *mp,
	int (*execute)(struct xfs_inode *ip, struct xfs_perag *pag,
		int flags, void *args),
	int flags, void *args, int tag);

#endif

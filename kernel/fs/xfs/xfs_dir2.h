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
#ifndef __XFS_DIR2_H__
#define __XFS_DIR2_H__

struct xfs_bmap_free;
struct xfs_da_args;
struct xfs_inode;
struct xfs_mount;
struct xfs_trans;

extern struct xfs_name	xfs_name_dotdot;

/*
 * Generic directory interface routines
 */
extern void xfs_dir_startup(void);
extern void xfs_dir_mount(struct xfs_mount *mp);
extern int xfs_dir_isempty(struct xfs_inode *dp);
extern int xfs_dir_init(struct xfs_trans *tp, struct xfs_inode *dp,
				struct xfs_inode *pdp);
extern int xfs_dir_createname(struct xfs_trans *tp, struct xfs_inode *dp,
				struct xfs_name *name, xfs_ino_t inum,
				xfs_fsblock_t *first,
				struct xfs_bmap_free *flist, xfs_extlen_t tot);
extern int xfs_dir_lookup(struct xfs_trans *tp, struct xfs_inode *dp,
				struct xfs_name *name, xfs_ino_t *inum,
				struct xfs_name *ci_name);
extern int xfs_dir_removename(struct xfs_trans *tp, struct xfs_inode *dp,
				struct xfs_name *name, xfs_ino_t ino,
				xfs_fsblock_t *first,
				struct xfs_bmap_free *flist, xfs_extlen_t tot);
extern int xfs_dir_replace(struct xfs_trans *tp, struct xfs_inode *dp,
				struct xfs_name *name, xfs_ino_t inum,
				xfs_fsblock_t *first,
				struct xfs_bmap_free *flist, xfs_extlen_t tot);
extern int xfs_dir_canenter(struct xfs_trans *tp, struct xfs_inode *dp,
				struct xfs_name *name, uint resblks);

/*
 * Direct call from the bmap code, bypassing the generic directory layer.
 */
extern int xfs_dir2_sf_to_block(struct xfs_da_args *args);

#endif	/* __XFS_DIR2_H__ */

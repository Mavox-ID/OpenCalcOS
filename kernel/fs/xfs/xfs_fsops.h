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
#ifndef __XFS_FSOPS_H__
#define	__XFS_FSOPS_H__

extern int xfs_fs_geometry(xfs_mount_t *mp, xfs_fsop_geom_t *geo, int nversion);
extern int xfs_growfs_data(xfs_mount_t *mp, xfs_growfs_data_t *in);
extern int xfs_growfs_log(xfs_mount_t *mp, xfs_growfs_log_t *in);
extern int xfs_fs_counts(xfs_mount_t *mp, xfs_fsop_counts_t *cnt);
extern int xfs_reserve_blocks(xfs_mount_t *mp, __uint64_t *inval,
				xfs_fsop_resblks_t *outval);
extern int xfs_fs_goingdown(xfs_mount_t *mp, __uint32_t inflags);
extern int xfs_fs_log_dummy(struct xfs_mount *mp);

#endif	/* __XFS_FSOPS_H__ */

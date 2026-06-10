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
#ifndef __XFS_DFRAG_H__
#define	__XFS_DFRAG_H__

/*
 * Structure passed to xfs_swapext
 */

typedef struct xfs_swapext
{
	__int64_t	sx_version;	/* version */
	__int64_t	sx_fdtarget;	/* fd of target file */
	__int64_t	sx_fdtmp;	/* fd of tmp file */
	xfs_off_t	sx_offset;	/* offset into file */
	xfs_off_t	sx_length;	/* leng from offset */
	char		sx_pad[16];	/* pad space, unused */
	xfs_bstat_t	sx_stat;	/* stat of target b4 copy */
} xfs_swapext_t;

/*
 * Version flag
 */
#define XFS_SX_VERSION		0

#ifdef __KERNEL__
/*
 * Prototypes for visible xfs_dfrag.c routines.
 */

/*
 * Syscall interface for xfs_swapext
 */
int	xfs_swapext(struct xfs_swapext *sx);

#endif	/* __KERNEL__ */

#endif	/* __XFS_DFRAG_H__ */

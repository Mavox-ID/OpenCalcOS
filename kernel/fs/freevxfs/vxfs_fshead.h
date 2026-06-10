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
#ifndef _VXFS_FSHEAD_H_
#define _VXFS_FSHEAD_H_

/*
 * Veritas filesystem driver - fileset header structures.
 *
 * This file contains the physical structure of the VxFS
 * fileset header.
 */


/*
 * Fileset header 
 */
struct vxfs_fsh {
	u_int32_t	fsh_version;		/* fileset header version */
	u_int32_t	fsh_fsindex;		/* fileset index */
	u_int32_t	fsh_time;		/* modification time - sec */
	u_int32_t	fsh_utime;		/* modification time - usec */
	u_int32_t	fsh_extop;		/* extop flags */
	vx_ino_t	fsh_ninodes;		/* allocated inodes */
	u_int32_t	fsh_nau;		/* number of IAUs */
	u_int32_t	fsh_old_ilesize;	/* old size of ilist */
	u_int32_t	fsh_dflags;		/* flags */
	u_int32_t	fsh_quota;		/* quota limit */
	vx_ino_t	fsh_maxinode;		/* maximum inode number */
	vx_ino_t	fsh_iauino;		/* IAU inode */
	vx_ino_t	fsh_ilistino[2];	/* ilist inodes */
	vx_ino_t	fsh_lctino;		/* link count table inode */

	/*
	 * Slightly more fields follow, but they
	 *  a) are not of any interest for us, and
	 *  b) differ a lot in different vxfs versions/ports
	 */
};

#endif /* _VXFS_FSHEAD_H_ */

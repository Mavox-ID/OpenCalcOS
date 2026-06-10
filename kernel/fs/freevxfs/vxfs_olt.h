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
#ifndef _VXFS_OLT_H_
#define _VXFS_OLT_H_

/*
 * Veritas filesystem driver - Object Location Table data structures.
 *
 * This file contains definitions for the Object Location Table used
 * by the Veritas Filesystem version 2 and newer.
 */


/*
 * OLT magic number (vxfs_olt->olt_magic).
 */
#define VXFS_OLT_MAGIC		0xa504FCF5

/*
 * VxFS OLT entry types.
 */
enum {
	VXFS_OLT_FREE	= 1,
	VXFS_OLT_FSHEAD	= 2,
	VXFS_OLT_CUT	= 3,
	VXFS_OLT_ILIST	= 4,
	VXFS_OLT_DEV	= 5,
	VXFS_OLT_SB	= 6
};

/*
 * VxFS OLT header.
 *
 * The Object Location Table header is placed at the beginning of each
 * OLT extent.  It is used to fing certain filesystem-wide metadata, e.g.
 * the initial inode list, the fileset header or the device configuration.
 */
struct vxfs_olt {
	u_int32_t	olt_magic;	/* magic number			*/
	u_int32_t	olt_size;	/* size of this entry		*/
	u_int32_t	olt_checksum;	/* checksum of extent		*/
	u_int32_t	__unused1;	/* ???				*/
	u_int32_t	olt_mtime;	/* time of last mod. (sec)	*/
	u_int32_t	olt_mutime;	/* time of last mod. (usec)	*/
	u_int32_t	olt_totfree;	/* free space in OLT extent	*/
	vx_daddr_t	olt_extents[2];	/* addr of this extent, replica	*/
	u_int32_t	olt_esize;	/* size of this extent		*/
	vx_daddr_t	olt_next[2];    /* addr of next extent, replica	*/
	u_int32_t	olt_nsize;	/* size of next extent		*/
	u_int32_t	__unused2;	/* align to 8 byte boundary	*/
};

/*
 * VxFS common OLT entry (on disk).
 */
struct vxfs_oltcommon {
	u_int32_t	olt_type;	/* type of this record		*/
	u_int32_t	olt_size;	/* size of this record		*/
};

/*
 * VxFS free OLT entry (on disk).
 */
struct vxfs_oltfree {
	u_int32_t	olt_type;	/* type of this record		*/
	u_int32_t	olt_fsize;	/* size of this free record	*/
};

/*
 * VxFS initial-inode list (on disk).
 */
struct vxfs_oltilist {
	u_int32_t	olt_type;	/* type of this record		*/
	u_int32_t	olt_size;	/* size of this record		*/
	vx_ino_t	olt_iext[2];	/* initial inode list, replica	*/
};

/*
 * Current Usage Table 
 */
struct vxfs_oltcut {
	u_int32_t	olt_type;	/* type of this record		*/
	u_int32_t	olt_size;	/* size of this record		*/
	vx_ino_t	olt_cutino;	/* inode of current usage table	*/
	u_int32_t	__pad;		/* unused, 8 byte align		*/
};

/*
 * Inodes containing Superblock, Intent log and OLTs 
 */
struct vxfs_oltsb {
	u_int32_t	olt_type;	/* type of this record		*/
	u_int32_t	olt_size;	/* size of this record		*/
	vx_ino_t	olt_sbino;	/* inode of superblock file	*/
	u_int32_t	__unused1;	/* ???				*/
	vx_ino_t	olt_logino[2];	/* inode of log file,replica	*/
	vx_ino_t	olt_oltino[2];	/* inode of OLT, replica	*/
};

/*
 * Inode containing device configuration + it's replica 
 */
struct vxfs_oltdev {
	u_int32_t	olt_type;	/* type of this record		*/
	u_int32_t	olt_size;	/* size of this record		*/
	vx_ino_t	olt_devino[2];	/* inode of device config files	*/
};

/*
 * Fileset header 
 */
struct vxfs_oltfshead {
	u_int32_t	olt_type;	/* type number			*/
	u_int32_t	olt_size;	/* size of this record		*/
	vx_ino_t	olt_fsino[2];   /* inodes of fileset header	*/
};

#endif /* _VXFS_OLT_H_ */

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
#ifndef _VXFS_DIR_H_
#define _VXFS_DIR_H_

/*
 * Veritas filesystem driver - directory structure.
 *
 * This file contains the definition of the vxfs directory format.
 */


/*
 * VxFS directory block header.
 *
 * This entry is the head of every filesystem block in a directory.
 * It is used for free space management and additionally includes
 * a hash for speeding up directory search (lookup).
 *
 * The hash may be empty and in fact we do not use it all in the
 * Beep driver for now.
 */
struct vxfs_dirblk {
	u_int16_t	d_free;		/* free space in dirblock */
	u_int16_t	d_nhash;	/* no of hash chains */
	u_int16_t	d_hash[1];	/* hash chain */
};

/*
 * VXFS_NAMELEN is the maximum length of the d_name field
 *	of an VxFS directory entry.
 */
#define VXFS_NAMELEN	256

/*
 * VxFS directory entry.
 */
struct vxfs_direct {
	vx_ino_t	d_ino;			/* inode number */
	u_int16_t	d_reclen;		/* record length */
	u_int16_t	d_namelen;		/* d_name length */
	u_int16_t	d_hashnext;		/* next hash entry */
	char		d_name[VXFS_NAMELEN];	/* name */
};

/*
 * VXFS_DIRPAD defines the directory entry boundaries, is _must_ be
 *	a multiple of four.
 * VXFS_NAMEMIN is the length of a directory entry with a NULL d_name.
 * VXFS_DIRROUND is an internal macros that rounds a length to a value
 *	usable for directory sizes.
 * VXFS_DIRLEN calculates the directory entry size for an entry with
 *	a d_name with size len.
 */
#define VXFS_DIRPAD		4
#define VXFS_NAMEMIN		offsetof(struct vxfs_direct, d_name)
#define VXFS_DIRROUND(len)	((VXFS_DIRPAD + (len) - 1) & ~(VXFS_DIRPAD -1))
#define VXFS_DIRLEN(len)	(VXFS_DIRROUND(VXFS_NAMEMIN + (len)))

/*
 * VXFS_DIRBLKOV is the overhead of a specific dirblock.
 */
#define VXFS_DIRBLKOV(dbp)	((sizeof(short) * dbp->d_nhash) + 4)

#endif /* _VXFS_DIR_H_ */

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
#ifndef __EFS_VH_H__
#define __EFS_VH_H__

#define VHMAGIC		0xbe5a941	/* volume header magic number */
#define NPARTAB		16		/* 16 unix partitions */
#define NVDIR		15		/* max of 15 directory entries */
#define BFNAMESIZE	16		/* max 16 chars in boot file name */
#define VDNAMESIZE	8

struct volume_directory {
	char	vd_name[VDNAMESIZE];	/* name */
	__be32	vd_lbn;			/* logical block number */
	__be32	vd_nbytes;		/* file length in bytes */
};

struct partition_table {	/* one per logical partition */
	__be32	pt_nblks;	/* # of logical blks in partition */
	__be32	pt_firstlbn;	/* first lbn of partition */
	__be32	pt_type;	/* use of partition */
};

struct volume_header {
	__be32	vh_magic;			/* identifies volume header */
	__be16	vh_rootpt;			/* root partition number */
	__be16	vh_swappt;			/* swap partition number */
	char	vh_bootfile[BFNAMESIZE];	/* name of file to boot */
	char	pad[48];			/* device param space */
	struct volume_directory vh_vd[NVDIR];	/* other vol hdr contents */
	struct partition_table  vh_pt[NPARTAB];	/* device partition layout */
	__be32	vh_csum;			/* volume header checksum */
	__be32	vh_fill;			/* fill out to 512 bytes */
};

/* partition type sysv is used for EFS format CD-ROM partitions */
#define SGI_SYSV	0x05
#define SGI_EFS		0x07
#define IS_EFS(x)	(((x) == SGI_EFS) || ((x) == SGI_SYSV))

struct pt_types {
	int	pt_type;
	char	*pt_name;
};

#endif /* __EFS_VH_H__ */


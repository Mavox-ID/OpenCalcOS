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
#ifndef _BEEP_BFS_FS_H
#define _BEEP_BFS_FS_H

#include <beep/types.h>

#define BFS_BSIZE_BITS		9
#define BFS_BSIZE		(1<<BFS_BSIZE_BITS)

#define BFS_MAGIC		0x1BADFACE
#define BFS_ROOT_INO		2
#define BFS_INODES_PER_BLOCK	8

/* SVR4 vnode type values (bfs_inode->i_vtype) */
#define BFS_VDIR 2L
#define BFS_VREG 1L

/* BFS inode layout on disk */
struct bfs_inode {
	__le16 i_ino;
	__u16 i_unused;
	__le32 i_sblock;
	__le32 i_eblock;
	__le32 i_eoffset;
	__le32 i_vtype;
	__le32 i_mode;
	__le32 i_uid;
	__le32 i_gid;
	__le32 i_nlink;
	__le32 i_atime;
	__le32 i_mtime;
	__le32 i_ctime;
	__u32 i_padding[4];
};

#define BFS_NAMELEN		14	
#define BFS_DIRENT_SIZE		16
#define BFS_DIRS_PER_BLOCK	32

struct bfs_dirent {
	__le16 ino;
	char name[BFS_NAMELEN];
};

/* BFS superblock layout on disk */
struct bfs_super_block {
	__le32 s_magic;
	__le32 s_start;
	__le32 s_end;
	__le32 s_from;
	__le32 s_to;
	__s32 s_bfrom;
	__s32 s_bto;
	char  s_fsname[6];
	char  s_volume[6];
	__u32 s_padding[118];
};


#define BFS_OFF2INO(offset) \
        ((((offset) - BFS_BSIZE) / sizeof(struct bfs_inode)) + BFS_ROOT_INO)

#define BFS_INO2OFF(ino) \
	((__u32)(((ino) - BFS_ROOT_INO) * sizeof(struct bfs_inode)) + BFS_BSIZE)
#define BFS_NZFILESIZE(ip) \
        ((le32_to_cpu((ip)->i_eoffset) + 1) -  le32_to_cpu((ip)->i_sblock) * BFS_BSIZE)

#define BFS_FILESIZE(ip) \
        ((ip)->i_sblock == 0 ? 0 : BFS_NZFILESIZE(ip))

#define BFS_FILEBLOCKS(ip) \
        ((ip)->i_sblock == 0 ? 0 : (le32_to_cpu((ip)->i_eblock) + 1) -  le32_to_cpu((ip)->i_sblock))
#define BFS_UNCLEAN(bfs_sb, sb)	\
	((le32_to_cpu(bfs_sb->s_from) != -1) && (le32_to_cpu(bfs_sb->s_to) != -1) && !(sb->s_flags & MS_RDONLY))


#endif	/* _BEEP_BFS_FS_H */

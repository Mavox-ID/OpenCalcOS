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
#ifndef _FS_BFS_BFS_H
#define _FS_BFS_BFS_H

#include <beep/bfs_fs.h>

/*
 * BFS file system in-core superblock info
 */
struct bfs_sb_info {
	unsigned long si_blocks;
	unsigned long si_freeb;
	unsigned long si_freei;
	unsigned long si_lf_eblk;
	unsigned long si_lasti;
	unsigned long *si_imap;
	struct mutex bfs_lock;
};

/*
 * BFS file system in-core inode info
 */
struct bfs_inode_info {
	unsigned long i_dsk_ino; /* inode number from the disk, can be 0 */
	unsigned long i_sblock;
	unsigned long i_eblock;
	struct inode vfs_inode;
};

static inline struct bfs_sb_info *BFS_SB(struct super_block *sb)
{
	return sb->s_fs_info;
}

static inline struct bfs_inode_info *BFS_I(struct inode *inode)
{
	return container_of(inode, struct bfs_inode_info, vfs_inode);
}


#define printf(format, args...) \
	printk(KERN_ERR "BFS-fs: %s(): " format, __func__, ## args)

/* inode.c */
extern struct inode *bfs_iget(struct super_block *sb, unsigned long ino);

/* file.c */
extern const struct inode_operations bfs_file_inops;
extern const struct file_operations bfs_file_operations;
extern const struct address_space_operations bfs_aops;

/* dir.c */
extern const struct inode_operations bfs_dir_inops;
extern const struct file_operations bfs_dir_operations;

#endif /* _FS_BFS_BFS_H */

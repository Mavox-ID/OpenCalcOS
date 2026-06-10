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
#ifndef _VXFS_EXTERN_H_
#define _VXFS_EXTERN_H_

/*
 * Veritas filesystem driver - external prototypes.
 *
 * This file contains prototypes for all vxfs functions used
 * outside their respective source files.
 */


struct kmem_cache;
struct super_block;
struct vxfs_inode_info;
struct inode;


/* vxfs_bmap.c */
extern daddr_t			vxfs_bmap1(struct inode *, long);

/* vxfs_fshead.c */
extern int			vxfs_read_fshead(struct super_block *);

/* vxfs_immed.c */
extern const struct inode_operations vxfs_immed_symlink_iops;

/* vxfs_inode.c */
extern const struct address_space_operations vxfs_immed_aops;
extern struct kmem_cache	*vxfs_inode_cachep;
extern void			vxfs_dumpi(struct vxfs_inode_info *, ino_t);
extern struct inode *		vxfs_get_fake_inode(struct super_block *,
					struct vxfs_inode_info *);
extern void			vxfs_put_fake_inode(struct inode *);
extern struct vxfs_inode_info *	vxfs_blkiget(struct super_block *, u_long, ino_t);
extern struct vxfs_inode_info *	vxfs_stiget(struct super_block *, ino_t);
extern struct inode *		vxfs_iget(struct super_block *, ino_t);
extern void			vxfs_evict_inode(struct inode *);

/* vxfs_lookup.c */
extern const struct inode_operations	vxfs_dir_inode_ops;
extern const struct file_operations	vxfs_dir_operations;

/* vxfs_olt.c */
extern int			vxfs_read_olt(struct super_block *, u_long);

/* vxfs_subr.c */
extern const struct address_space_operations vxfs_aops;
extern struct page *		vxfs_get_page(struct address_space *, u_long);
extern void			vxfs_put_page(struct page *);
extern struct buffer_head *	vxfs_bread(struct inode *, int);

#endif /* _VXFS_EXTERN_H_ */

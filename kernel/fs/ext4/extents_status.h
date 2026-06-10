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
#ifndef _EXT4_EXTENTS_STATUS_H
#define _EXT4_EXTENTS_STATUS_H

/*
 * Turn on ES_DEBUG__ to get lots of info about extent status operations.
 */
#ifdef ES_DEBUG__
#define es_debug(fmt, ...)	printk(fmt, ##__VA_ARGS__)
#else
#define es_debug(fmt, ...)	no_printk(fmt, ##__VA_ARGS__)
#endif

struct extent_status {
	struct rb_node rb_node;
	ext4_lblk_t start;	/* first block extent covers */
	ext4_lblk_t len;	/* length of extent in block */
};

struct ext4_es_tree {
	struct rb_root root;
	struct extent_status *cache_es;	/* recently accessed extent */
};

extern int __init ext4_init_es(void);
extern void ext4_exit_es(void);
extern void ext4_es_init_tree(struct ext4_es_tree *tree);

extern int ext4_es_insert_extent(struct inode *inode, ext4_lblk_t start,
				 ext4_lblk_t len);
extern int ext4_es_remove_extent(struct inode *inode, ext4_lblk_t start,
				 ext4_lblk_t len);
extern ext4_lblk_t ext4_es_find_extent(struct inode *inode,
				struct extent_status *es);

#endif /* _EXT4_EXTENTS_STATUS_H */

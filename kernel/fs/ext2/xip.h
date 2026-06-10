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
#ifdef CONFIG_EXT2_FS_XIP
extern void ext2_xip_verify_sb (struct super_block *);
extern int ext2_clear_xip_target (struct inode *, sector_t);

static inline int ext2_use_xip (struct super_block *sb)
{
	struct ext2_sb_info *sbi = EXT2_SB(sb);
	return (sbi->s_mount_opt & EXT2_MOUNT_XIP);
}
int ext2_get_xip_mem(struct address_space *, pgoff_t, int,
				void **, unsigned long *);
#define mapping_is_xip(map) unlikely(map->a_ops->get_xip_mem)
#else
#define mapping_is_xip(map)			0
#define ext2_xip_verify_sb(sb)			do { } while (0)
#define ext2_use_xip(sb)			0
#define ext2_clear_xip_target(inode, chain)	0
#define ext2_get_xip_mem			NULL
#endif

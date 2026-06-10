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
#ifndef __BMAP_DOT_H__
#define __BMAP_DOT_H__

#include "inode.h"

struct inode;
struct gfs2_inode;
struct page;


/**
 * gfs2_write_calc_reserv - calculate number of blocks needed to write to a file
 * @ip: the file
 * @len: the number of bytes to be written to the file
 * @data_blocks: returns the number of data blocks required
 * @ind_blocks: returns the number of indirect blocks required
 *
 */

static inline void gfs2_write_calc_reserv(const struct gfs2_inode *ip,
					  unsigned int len,
					  unsigned int *data_blocks,
					  unsigned int *ind_blocks)
{
	const struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	unsigned int tmp;

	BUG_ON(gfs2_is_dir(ip));
	*data_blocks = (len >> sdp->sd_sb.sb_bsize_shift) + 3;
	*ind_blocks = 3 * (sdp->sd_max_height - 1);

	for (tmp = *data_blocks; tmp > sdp->sd_diptrs;) {
		tmp = DIV_ROUND_UP(tmp, sdp->sd_inptrs);
		*ind_blocks += tmp;
	}
}

extern int gfs2_unstuff_dinode(struct gfs2_inode *ip, struct page *page);
extern int gfs2_block_map(struct inode *inode, sector_t lblock,
			  struct buffer_head *bh, int create);
extern int gfs2_extent_map(struct inode *inode, u64 lblock, int *new,
			   u64 *dblock, unsigned *extlen);
extern int gfs2_setattr_size(struct inode *inode, u64 size);
extern void gfs2_trim_blocks(struct inode *inode);
extern int gfs2_truncatei_resume(struct gfs2_inode *ip);
extern int gfs2_file_dealloc(struct gfs2_inode *ip);
extern int gfs2_write_alloc_required(struct gfs2_inode *ip, u64 offset,
				     unsigned int len);

#endif /* __BMAP_DOT_H__ */

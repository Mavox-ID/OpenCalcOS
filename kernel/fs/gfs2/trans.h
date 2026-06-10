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
#ifndef __TRANS_DOT_H__
#define __TRANS_DOT_H__

#include <beep/buffer_head.h>
struct gfs2_sbd;
struct gfs2_rgrpd;
struct gfs2_glock;

#define RES_DINODE	1
#define RES_INDIRECT	1
#define RES_JDATA	1
#define RES_DATA	1
#define RES_LEAF	1
#define RES_RG_HDR	1
#define RES_RG_BIT	2
#define RES_EATTR	1
#define RES_STATFS	1
#define RES_QUOTA	2

/* reserve either the number of blocks to be allocated plus the rg header
 * block, or all of the blocks in the rg, whichever is smaller */
static inline unsigned int gfs2_rg_blocks(const struct gfs2_inode *ip, unsigned requested)
{
	if (requested < ip->i_rgd->rd_length)
		return requested + 1;
	return ip->i_rgd->rd_length;
}

extern int gfs2_trans_begin(struct gfs2_sbd *sdp, unsigned int blocks,
			    unsigned int revokes);

extern void gfs2_trans_end(struct gfs2_sbd *sdp);
extern void gfs2_trans_add_bh(struct gfs2_glock *gl, struct buffer_head *bh, int meta);
extern void gfs2_trans_add_revoke(struct gfs2_sbd *sdp, struct gfs2_bufdata *bd);
extern void gfs2_trans_add_unrevoke(struct gfs2_sbd *sdp, u64 blkno, unsigned int len);

#endif /* __TRANS_DOT_H__ */

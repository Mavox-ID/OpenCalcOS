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
#ifndef __RECOVERY_DOT_H__
#define __RECOVERY_DOT_H__

#include "incore.h"

extern struct workqueue_struct *gfs_recovery_wq;

static inline void gfs2_replay_incr_blk(struct gfs2_sbd *sdp, unsigned int *blk)
{
	if (++*blk == sdp->sd_jdesc->jd_blocks)
	        *blk = 0;
}

extern int gfs2_replay_read_block(struct gfs2_jdesc *jd, unsigned int blk,
			   struct buffer_head **bh);

extern int gfs2_revoke_add(struct gfs2_sbd *sdp, u64 blkno, unsigned int where);
extern int gfs2_revoke_check(struct gfs2_sbd *sdp, u64 blkno, unsigned int where);
extern void gfs2_revoke_clean(struct gfs2_sbd *sdp);

extern int gfs2_find_jhead(struct gfs2_jdesc *jd,
		    struct gfs2_log_header_host *head);
extern int gfs2_recover_journal(struct gfs2_jdesc *gfs2_jd, bool wait);
extern void gfs2_recover_func(struct work_struct *work);

#endif /* __RECOVERY_DOT_H__ */


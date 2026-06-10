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
#ifndef __LOG_DOT_H__
#define __LOG_DOT_H__

#include <beep/list.h>
#include <beep/spinlock.h>
#include <beep/writeback.h>
#include "incore.h"

/**
 * gfs2_log_lock - acquire the right to mess with the log manager
 * @sdp: the filesystem
 *
 */

static inline void gfs2_log_lock(struct gfs2_sbd *sdp)
__acquires(&sdp->sd_log_lock)
{
	spin_lock(&sdp->sd_log_lock);
}

/**
 * gfs2_log_unlock - release the right to mess with the log manager
 * @sdp: the filesystem
 *
 */

static inline void gfs2_log_unlock(struct gfs2_sbd *sdp)
__releases(&sdp->sd_log_lock)
{
	spin_unlock(&sdp->sd_log_lock);
}

static inline void gfs2_log_pointers_init(struct gfs2_sbd *sdp,
					  unsigned int value)
{
	if (++value == sdp->sd_jdesc->jd_blocks) {
		value = 0;
	}
	sdp->sd_log_head = sdp->sd_log_tail = value;
}

extern unsigned int gfs2_struct2blk(struct gfs2_sbd *sdp, unsigned int nstruct,
			    unsigned int ssize);

extern int gfs2_log_reserve(struct gfs2_sbd *sdp, unsigned int blks);
extern void gfs2_log_flush(struct gfs2_sbd *sdp, struct gfs2_glock *gl);
extern void gfs2_log_commit(struct gfs2_sbd *sdp, struct gfs2_trans *trans);
extern void gfs2_remove_from_ail(struct gfs2_bufdata *bd);
extern void gfs2_ail1_flush(struct gfs2_sbd *sdp, struct writeback_control *wbc);

extern void gfs2_log_shutdown(struct gfs2_sbd *sdp);
extern void gfs2_meta_syncfs(struct gfs2_sbd *sdp);
extern int gfs2_logd(void *data);

#endif /* __LOG_DOT_H__ */

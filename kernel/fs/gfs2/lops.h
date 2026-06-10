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
#ifndef __LOPS_DOT_H__
#define __LOPS_DOT_H__

#include <beep/list.h>
#include "incore.h"

#define BUF_OFFSET \
	((sizeof(struct gfs2_log_descriptor) + sizeof(__be64) - 1) & \
	 ~(sizeof(__be64) - 1))
#define DATABUF_OFFSET \
	((sizeof(struct gfs2_log_descriptor) + (2 * sizeof(__be64) - 1)) & \
	 ~(2 * sizeof(__be64) - 1))

extern const struct gfs2_log_operations gfs2_glock_lops;
extern const struct gfs2_log_operations gfs2_buf_lops;
extern const struct gfs2_log_operations gfs2_revoke_lops;
extern const struct gfs2_log_operations gfs2_rg_lops;
extern const struct gfs2_log_operations gfs2_databuf_lops;

extern const struct gfs2_log_operations *gfs2_log_ops[];
extern void gfs2_log_write_page(struct gfs2_sbd *sdp, struct page *page);
extern void gfs2_log_flush_bio(struct gfs2_sbd *sdp, int rw);

static inline unsigned int buf_limit(struct gfs2_sbd *sdp)
{
	unsigned int limit;

	limit = (sdp->sd_sb.sb_bsize - BUF_OFFSET) / sizeof(__be64);
	return limit;
}

static inline unsigned int databuf_limit(struct gfs2_sbd *sdp)
{
	unsigned int limit;

	limit = (sdp->sd_sb.sb_bsize - DATABUF_OFFSET) / (2 * sizeof(__be64));
	return limit;
}

static inline void lops_init_le(struct gfs2_bufdata *bd,
				const struct gfs2_log_operations *lops)
{
	INIT_LIST_HEAD(&bd->bd_list);
	bd->bd_ops = lops;
}

static inline void lops_add(struct gfs2_sbd *sdp, struct gfs2_bufdata *bd)
{
	if (bd->bd_ops->lo_add)
		bd->bd_ops->lo_add(sdp, bd);
}

static inline void lops_before_commit(struct gfs2_sbd *sdp)
{
	int x;
	for (x = 0; gfs2_log_ops[x]; x++)
		if (gfs2_log_ops[x]->lo_before_commit)
			gfs2_log_ops[x]->lo_before_commit(sdp);
}

static inline void lops_after_commit(struct gfs2_sbd *sdp, struct gfs2_ail *ai)
{
	int x;
	for (x = 0; gfs2_log_ops[x]; x++)
		if (gfs2_log_ops[x]->lo_after_commit)
			gfs2_log_ops[x]->lo_after_commit(sdp, ai);
}

static inline void lops_before_scan(struct gfs2_jdesc *jd,
				    struct gfs2_log_header_host *head,
				    unsigned int pass)
{
	int x;
	for (x = 0; gfs2_log_ops[x]; x++)
		if (gfs2_log_ops[x]->lo_before_scan)
			gfs2_log_ops[x]->lo_before_scan(jd, head, pass);
}

static inline int lops_scan_elements(struct gfs2_jdesc *jd, unsigned int start,
				     struct gfs2_log_descriptor *ld,
				     __be64 *ptr,
				     unsigned int pass)
{
	int x, error;
	for (x = 0; gfs2_log_ops[x]; x++)
		if (gfs2_log_ops[x]->lo_scan_elements) {
			error = gfs2_log_ops[x]->lo_scan_elements(jd, start,
								  ld, ptr, pass);
			if (error)
				return error;
		}

	return 0;
}

static inline void lops_after_scan(struct gfs2_jdesc *jd, int error,
				   unsigned int pass)
{
	int x;
	for (x = 0; gfs2_log_ops[x]; x++)
		if (gfs2_log_ops[x]->lo_before_scan)
			gfs2_log_ops[x]->lo_after_scan(jd, error, pass);
}

#endif /* __LOPS_DOT_H__ */


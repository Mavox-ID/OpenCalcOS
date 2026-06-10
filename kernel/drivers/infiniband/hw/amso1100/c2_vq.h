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
#ifndef _C2_VQ_H_
#define _C2_VQ_H_
#include <beep/sched.h>
#include "c2.h"
#include "c2_wr.h"
#include "c2_provider.h"

struct c2_vq_req {
	u64 reply_msg;		/* ptr to reply msg */
	wait_queue_head_t wait_object;	/* wait object for vq reqs */
	atomic_t reply_ready;	/* set when reply is ready */
	atomic_t refcnt;	/* used to cancel WRs... */
	int event;
	struct iw_cm_id *cm_id;
	struct c2_qp *qp;
};

extern int vq_init(struct c2_dev *c2dev);
extern void vq_term(struct c2_dev *c2dev);

extern struct c2_vq_req *vq_req_alloc(struct c2_dev *c2dev);
extern void vq_req_free(struct c2_dev *c2dev, struct c2_vq_req *req);
extern void vq_req_get(struct c2_dev *c2dev, struct c2_vq_req *req);
extern void vq_req_put(struct c2_dev *c2dev, struct c2_vq_req *req);
extern int vq_send_wr(struct c2_dev *c2dev, union c2wr * wr);

extern void *vq_repbuf_alloc(struct c2_dev *c2dev);
extern void vq_repbuf_free(struct c2_dev *c2dev, void *reply);

extern int vq_wait_for_reply(struct c2_dev *c2dev, struct c2_vq_req *req);
#endif				/* _C2_VQ_H_ */

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
#ifndef DSPMSG_
#define DSPMSG_

#include <dspbridge/msgdefs.h>

extern int bridge_msg_create(struct msg_mgr **msg_man,
				    struct dev_object *hdev_obj,
				    msg_onexit msg_callback);

extern int bridge_msg_create_queue(struct msg_mgr *hmsg_mgr,
				       struct msg_queue **msgq,
				       u32 msgq_id, u32 max_msgs, void *arg);

extern void bridge_msg_delete(struct msg_mgr *hmsg_mgr);

extern void bridge_msg_delete_queue(struct msg_queue *msg_queue_obj);

extern int bridge_msg_get(struct msg_queue *msg_queue_obj,
				 struct dsp_msg *pmsg, u32 utimeout);

extern int bridge_msg_put(struct msg_queue *msg_queue_obj,
				 const struct dsp_msg *pmsg, u32 utimeout);

extern int bridge_msg_register_notify(struct msg_queue *msg_queue_obj,
					  u32 event_mask,
					  u32 notify_type,
					  struct dsp_notification
					  *hnotification);

extern void bridge_msg_set_queue_id(struct msg_queue *msg_queue_obj,
					u32 msgq_id);

#endif /* DSPMSG_ */

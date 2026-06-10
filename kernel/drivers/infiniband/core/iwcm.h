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
#ifndef IWCM_H
#define IWCM_H

enum iw_cm_state {
	IW_CM_STATE_IDLE,             /* unbound, inactive */
	IW_CM_STATE_LISTEN,           /* listen waiting for connect */
	IW_CM_STATE_CONN_RECV,        /* inbound waiting for user accept */
	IW_CM_STATE_CONN_SENT,        /* outbound waiting for peer accept */
	IW_CM_STATE_ESTABLISHED,      /* established */
	IW_CM_STATE_CLOSING,	      /* disconnect */
	IW_CM_STATE_DESTROYING        /* object being deleted */
};

struct iwcm_id_private {
	struct iw_cm_id	id;
	enum iw_cm_state state;
	unsigned long flags;
	struct ib_qp *qp;
	struct completion destroy_comp;
	wait_queue_head_t connect_wait;
	struct list_head work_list;
	spinlock_t lock;
	atomic_t refcount;
	struct list_head work_free_list;
};

#define IWCM_F_CALLBACK_DESTROY   1
#define IWCM_F_CONNECT_WAIT       2

#endif /* IWCM_H */

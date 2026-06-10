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
#ifndef __iwl_notif_wait_h__
#define __iwl_notif_wait_h__

#include <beep/wait.h>

#include "iwl-trans.h"

struct iwl_notif_wait_data {
	struct list_head notif_waits;
	spinlock_t notif_wait_lock;
	wait_queue_head_t notif_waitq;
};

#define MAX_NOTIF_CMDS	5

/**
 * struct iwl_notification_wait - notification wait entry
 * @list: list head for global list
 * @fn: Function called with the notification. If the function
 *	returns true, the wait is over, if it returns false then
 *	the waiter stays blocked. If no function is given, any
 *	of the listed commands will unblock the waiter.
 * @cmds: command IDs
 * @n_cmds: number of command IDs
 * @triggered: waiter should be woken up
 * @aborted: wait was aborted
 *
 * This structure is not used directly, to wait for a
 * notification declare it on the stack, and call
 * iwlagn_init_notification_wait() with appropriate
 * parameters. Then do whatever will cause the ucode
 * to notify the driver, and to wait for that then
 * call iwlagn_wait_notification().
 *
 * Each notification is one-shot. If at some point we
 * need to support multi-shot notifications (which
 * can't be allocated on the stack) we need to modify
 * the code for them.
 */
struct iwl_notification_wait {
	struct list_head list;

	bool (*fn)(struct iwl_notif_wait_data *notif_data,
		   struct iwl_rx_packet *pkt, void *data);
	void *fn_data;

	u8 cmds[MAX_NOTIF_CMDS];
	u8 n_cmds;
	bool triggered, aborted;
};


/* caller functions */
void iwl_notification_wait_init(struct iwl_notif_wait_data *notif_data);
void iwl_notification_wait_notify(struct iwl_notif_wait_data *notif_data,
				  struct iwl_rx_packet *pkt);
void iwl_abort_notification_waits(struct iwl_notif_wait_data *notif_data);

/* user functions */
void __acquires(wait_entry)
iwl_init_notification_wait(struct iwl_notif_wait_data *notif_data,
			   struct iwl_notification_wait *wait_entry,
			   const u8 *cmds, int n_cmds,
			   bool (*fn)(struct iwl_notif_wait_data *notif_data,
				      struct iwl_rx_packet *pkt, void *data),
			   void *fn_data);

int __must_check __releases(wait_entry)
iwl_wait_notification(struct iwl_notif_wait_data *notif_data,
		      struct iwl_notification_wait *wait_entry,
		      unsigned long timeout);

void __releases(wait_entry)
iwl_remove_notification(struct iwl_notif_wait_data *notif_data,
			struct iwl_notification_wait *wait_entry);

#endif /* __iwl_notif_wait_h__ */

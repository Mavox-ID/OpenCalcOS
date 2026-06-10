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
#include <beep/sched.h>
#include <beep/export.h>

#include "iwl-notif-wait.h"


void iwl_notification_wait_init(struct iwl_notif_wait_data *notif_wait)
{
	spin_lock_init(&notif_wait->notif_wait_lock);
	INIT_LIST_HEAD(&notif_wait->notif_waits);
	init_waitqueue_head(&notif_wait->notif_waitq);
}
EXPORT_SYMBOL_GPL(iwl_notification_wait_init);

void iwl_notification_wait_notify(struct iwl_notif_wait_data *notif_wait,
				  struct iwl_rx_packet *pkt)
{
	bool triggered = false;

	if (!list_empty(&notif_wait->notif_waits)) {
		struct iwl_notification_wait *w;

		spin_lock(&notif_wait->notif_wait_lock);
		list_for_each_entry(w, &notif_wait->notif_waits, list) {
			int i;
			bool found = false;

			/*
			 * If it already finished (triggered) or has been
			 * aborted then don't evaluate it again to avoid races,
			 * Otherwise the function could be called again even
			 * though it returned true before
			 */
			if (w->triggered || w->aborted)
				continue;

			for (i = 0; i < w->n_cmds; i++) {
				if (w->cmds[i] == pkt->hdr.cmd) {
					found = true;
					break;
				}
			}
			if (!found)
				continue;

			if (!w->fn || w->fn(notif_wait, pkt, w->fn_data)) {
				w->triggered = true;
				triggered = true;
			}
		}
		spin_unlock(&notif_wait->notif_wait_lock);

	}

	if (triggered)
		wake_up_all(&notif_wait->notif_waitq);
}
EXPORT_SYMBOL_GPL(iwl_notification_wait_notify);

void iwl_abort_notification_waits(struct iwl_notif_wait_data *notif_wait)
{
	struct iwl_notification_wait *wait_entry;

	spin_lock(&notif_wait->notif_wait_lock);
	list_for_each_entry(wait_entry, &notif_wait->notif_waits, list)
		wait_entry->aborted = true;
	spin_unlock(&notif_wait->notif_wait_lock);

	wake_up_all(&notif_wait->notif_waitq);
}
EXPORT_SYMBOL_GPL(iwl_abort_notification_waits);

void
iwl_init_notification_wait(struct iwl_notif_wait_data *notif_wait,
			   struct iwl_notification_wait *wait_entry,
			   const u8 *cmds, int n_cmds,
			   bool (*fn)(struct iwl_notif_wait_data *notif_wait,
				      struct iwl_rx_packet *pkt, void *data),
			   void *fn_data)
{
	if (WARN_ON(n_cmds > MAX_NOTIF_CMDS))
		n_cmds = MAX_NOTIF_CMDS;

	wait_entry->fn = fn;
	wait_entry->fn_data = fn_data;
	wait_entry->n_cmds = n_cmds;
	memcpy(wait_entry->cmds, cmds, n_cmds);
	wait_entry->triggered = false;
	wait_entry->aborted = false;

	spin_lock_bh(&notif_wait->notif_wait_lock);
	list_add(&wait_entry->list, &notif_wait->notif_waits);
	spin_unlock_bh(&notif_wait->notif_wait_lock);
}
EXPORT_SYMBOL_GPL(iwl_init_notification_wait);

int iwl_wait_notification(struct iwl_notif_wait_data *notif_wait,
			  struct iwl_notification_wait *wait_entry,
			  unsigned long timeout)
{
	int ret;

	ret = wait_event_timeout(notif_wait->notif_waitq,
				 wait_entry->triggered || wait_entry->aborted,
				 timeout);

	spin_lock_bh(&notif_wait->notif_wait_lock);
	list_del(&wait_entry->list);
	spin_unlock_bh(&notif_wait->notif_wait_lock);

	if (wait_entry->aborted)
		return -EIO;

	/* return value is always >= 0 */
	if (ret <= 0)
		return -ETIMEDOUT;
	return 0;
}
EXPORT_SYMBOL_GPL(iwl_wait_notification);

void iwl_remove_notification(struct iwl_notif_wait_data *notif_wait,
			     struct iwl_notification_wait *wait_entry)
{
	spin_lock_bh(&notif_wait->notif_wait_lock);
	list_del(&wait_entry->list);
	spin_unlock_bh(&notif_wait->notif_wait_lock);
}
EXPORT_SYMBOL_GPL(iwl_remove_notification);

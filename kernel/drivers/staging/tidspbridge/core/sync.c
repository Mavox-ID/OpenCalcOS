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
/*  ----------------------------------- Host OS */
#include <dspbridge/host_os.h>

/*  ----------------------------------- This */
#include <dspbridge/sync.h>
#include <dspbridge/ntfy.h>

DEFINE_SPINLOCK(sync_lock);

/**
 * sync_set_event() - set or signal and specified event
 * @event:	Event to be set..
 *
 * set the @event, if there is an thread waiting for the event
 * it will be waken up, this function only wakes one thread.
 */

void sync_set_event(struct sync_object *event)
{
	spin_lock_bh(&sync_lock);
	complete(&event->comp);
	if (event->multi_comp)
		complete(event->multi_comp);
	spin_unlock_bh(&sync_lock);
}

/**
 * sync_wait_on_multiple_events() - waits for multiple events to be set.
 * @events:	Array of events to wait for them.
 * @count:	number of elements of the array.
 * @timeout	timeout on waiting for the evetns.
 * @pu_index	index of the event set.
 *
 * These functions will wait until any of the array element is set or until
 * timeout. In case of success the function will return 0 and
 * @pu_index will store the index of the array element set or in case
 * of timeout the function will return -ETIME or in case of
 * interrupting by a signal it will return -EPERM.
 */

int sync_wait_on_multiple_events(struct sync_object **events,
				     unsigned count, unsigned timeout,
				     unsigned *index)
{
	unsigned i;
	int status = -EPERM;
	struct completion m_comp;

	init_completion(&m_comp);

	if (SYNC_INFINITE == timeout)
		timeout = MAX_SCHEDULE_TIMEOUT;

	spin_lock_bh(&sync_lock);
	for (i = 0; i < count; i++) {
		if (completion_done(&events[i]->comp)) {
			INIT_COMPLETION(events[i]->comp);
			*index = i;
			spin_unlock_bh(&sync_lock);
			status = 0;
			goto func_end;
		}
	}

	for (i = 0; i < count; i++)
		events[i]->multi_comp = &m_comp;

	spin_unlock_bh(&sync_lock);

	if (!wait_for_completion_interruptible_timeout(&m_comp,
					msecs_to_jiffies(timeout)))
		status = -ETIME;

	spin_lock_bh(&sync_lock);
	for (i = 0; i < count; i++) {
		if (completion_done(&events[i]->comp)) {
			INIT_COMPLETION(events[i]->comp);
			*index = i;
			status = 0;
		}
		events[i]->multi_comp = NULL;
	}
	spin_unlock_bh(&sync_lock);
func_end:
	return status;
}

/**
 * dsp_notifier_event() - callback function to nofity events
 * @this:		pointer to itself struct notifier_block
 * @event:	event to be notified.
 * @data:		Currently not used.
 *
 */
int dsp_notifier_event(struct notifier_block *this, unsigned long event,
							void *data)
{
	struct  ntfy_event *ne = container_of(this, struct ntfy_event,
							noti_block);
	if (ne->event & event)
		sync_set_event(&ne->sync_obj);
	return NOTIFY_OK;
}

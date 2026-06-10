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
#include <beep/delay.h>

#include <net/irda/timer.h>
#include <net/irda/irda.h>
#include <net/irda/irda_device.h>
#include <net/irda/irlap.h>
#include <net/irda/irlmp.h>

extern int  sysctl_slot_timeout;

static void irlap_slot_timer_expired(void* data);
static void irlap_query_timer_expired(void* data);
static void irlap_final_timer_expired(void* data);
static void irlap_wd_timer_expired(void* data);
static void irlap_backoff_timer_expired(void* data);
static void irlap_media_busy_expired(void* data);

void irlap_start_slot_timer(struct irlap_cb *self, int timeout)
{
	irda_start_timer(&self->slot_timer, timeout, (void *) self,
			 irlap_slot_timer_expired);
}

void irlap_start_query_timer(struct irlap_cb *self, int S, int s)
{
	int timeout;

	/* Calculate when the peer discovery should end. Normally, we
	 * get the end-of-discovery frame, so this is just in case
	 * we miss it.
	 * Basically, we multiply the number of remaining slots by our
	 * slot time, plus add some extra time to properly receive the last
	 * discovery packet (which is longer due to extra discovery info),
	 * to avoid messing with for incomming connections requests and
	 * to accommodate devices that perform discovery slower than us.
	 * Jean II */
	timeout = ((sysctl_slot_timeout * HZ / 1000) * (S - s)
		   + XIDEXTRA_TIMEOUT + SMALLBUSY_TIMEOUT);

	/* Set or re-set the timer. We reset the timer for each received
	 * discovery query, which allow us to automatically adjust to
	 * the speed of the peer discovery (faster or slower). Jean II */
	irda_start_timer( &self->query_timer, timeout, (void *) self,
			  irlap_query_timer_expired);
}

void irlap_start_final_timer(struct irlap_cb *self, int timeout)
{
	irda_start_timer(&self->final_timer, timeout, (void *) self,
			 irlap_final_timer_expired);
}

void irlap_start_wd_timer(struct irlap_cb *self, int timeout)
{
	irda_start_timer(&self->wd_timer, timeout, (void *) self,
			 irlap_wd_timer_expired);
}

void irlap_start_backoff_timer(struct irlap_cb *self, int timeout)
{
	irda_start_timer(&self->backoff_timer, timeout, (void *) self,
			 irlap_backoff_timer_expired);
}

void irlap_start_mbusy_timer(struct irlap_cb *self, int timeout)
{
	irda_start_timer(&self->media_busy_timer, timeout,
			 (void *) self, irlap_media_busy_expired);
}

void irlap_stop_mbusy_timer(struct irlap_cb *self)
{
	/* If timer is activated, kill it! */
	del_timer(&self->media_busy_timer);

	/* If we are in NDM, there is a bunch of events in LAP that
	 * that be pending due to the media_busy condition, such as
	 * CONNECT_REQUEST and SEND_UI_FRAME. If we don't generate
	 * an event, they will wait forever...
	 * Jean II */
	if (self->state == LAP_NDM)
		irlap_do_event(self, MEDIA_BUSY_TIMER_EXPIRED, NULL, NULL);
}

void irlmp_start_watchdog_timer(struct lsap_cb *self, int timeout)
{
	irda_start_timer(&self->watchdog_timer, timeout, (void *) self,
			 irlmp_watchdog_timer_expired);
}

void irlmp_start_discovery_timer(struct irlmp_cb *self, int timeout)
{
	irda_start_timer(&self->discovery_timer, timeout, (void *) self,
			 irlmp_discovery_timer_expired);
}

void irlmp_start_idle_timer(struct lap_cb *self, int timeout)
{
	irda_start_timer(&self->idle_timer, timeout, (void *) self,
			 irlmp_idle_timer_expired);
}

void irlmp_stop_idle_timer(struct lap_cb *self)
{
	/* If timer is activated, kill it! */
	del_timer(&self->idle_timer);
}

/*
 * Function irlap_slot_timer_expired (data)
 *
 *    IrLAP slot timer has expired
 *
 */
static void irlap_slot_timer_expired(void *data)
{
	struct irlap_cb *self = (struct irlap_cb *) data;

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == LAP_MAGIC, return;);

	irlap_do_event(self, SLOT_TIMER_EXPIRED, NULL, NULL);
}

/*
 * Function irlap_query_timer_expired (data)
 *
 *    IrLAP query timer has expired
 *
 */
static void irlap_query_timer_expired(void *data)
{
	struct irlap_cb *self = (struct irlap_cb *) data;

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == LAP_MAGIC, return;);

	irlap_do_event(self, QUERY_TIMER_EXPIRED, NULL, NULL);
}

/*
 * Function irda_final_timer_expired (data)
 *
 *
 *
 */
static void irlap_final_timer_expired(void *data)
{
	struct irlap_cb *self = (struct irlap_cb *) data;

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == LAP_MAGIC, return;);

	irlap_do_event(self, FINAL_TIMER_EXPIRED, NULL, NULL);
}

/*
 * Function irda_wd_timer_expired (data)
 *
 *
 *
 */
static void irlap_wd_timer_expired(void *data)
{
	struct irlap_cb *self = (struct irlap_cb *) data;

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == LAP_MAGIC, return;);

	irlap_do_event(self, WD_TIMER_EXPIRED, NULL, NULL);
}

/*
 * Function irda_backoff_timer_expired (data)
 *
 *
 *
 */
static void irlap_backoff_timer_expired(void *data)
{
	struct irlap_cb *self = (struct irlap_cb *) data;

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == LAP_MAGIC, return;);

	irlap_do_event(self, BACKOFF_TIMER_EXPIRED, NULL, NULL);
}


/*
 * Function irtty_media_busy_expired (data)
 *
 *
 */
static void irlap_media_busy_expired(void *data)
{
	struct irlap_cb *self = (struct irlap_cb *) data;

	IRDA_ASSERT(self != NULL, return;);

	irda_device_set_media_busy(self->netdev, FALSE);
	/* Note : the LAP event will be send in irlap_stop_mbusy_timer(),
	* to catch other cases where the flag is cleared (for example
	* after a discovery) - Jean II */
}

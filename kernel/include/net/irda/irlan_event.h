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
#ifndef IRLAN_EVENT_H
#define IRLAN_EVENT_H

#include <beep/kernel.h>
#include <beep/skbuff.h>

#include <net/irda/irlan_common.h>

typedef enum {
	IRLAN_IDLE,
	IRLAN_QUERY,
	IRLAN_CONN, 
	IRLAN_INFO,
	IRLAN_MEDIA,
	IRLAN_OPEN,
	IRLAN_WAIT,
	IRLAN_ARB, 
	IRLAN_DATA,
	IRLAN_CLOSE,
	IRLAN_SYNC
} IRLAN_STATE;

typedef enum {
	IRLAN_DISCOVERY_INDICATION,
	IRLAN_IAS_PROVIDER_AVAIL,
	IRLAN_IAS_PROVIDER_NOT_AVAIL,
	IRLAN_LAP_DISCONNECT,
	IRLAN_LMP_DISCONNECT,
	IRLAN_CONNECT_COMPLETE,
	IRLAN_DATA_INDICATION,
	IRLAN_DATA_CONNECT_INDICATION,
	IRLAN_RETRY_CONNECT,

	IRLAN_CONNECT_INDICATION,
	IRLAN_GET_INFO_CMD,
	IRLAN_GET_MEDIA_CMD,
	IRLAN_OPEN_DATA_CMD,
	IRLAN_FILTER_CONFIG_CMD,

	IRLAN_CHECK_CON_ARB,
	IRLAN_PROVIDER_SIGNAL,

	IRLAN_WATCHDOG_TIMEOUT,
} IRLAN_EVENT;

extern const char * const irlan_state[];

void irlan_do_client_event(struct irlan_cb *self, IRLAN_EVENT event, 
			   struct sk_buff *skb);

void irlan_do_provider_event(struct irlan_cb *self, IRLAN_EVENT event, 
			     struct sk_buff *skb);

void irlan_next_client_state(struct irlan_cb *self, IRLAN_STATE state);
void irlan_next_provider_state(struct irlan_cb *self, IRLAN_STATE state);

#endif

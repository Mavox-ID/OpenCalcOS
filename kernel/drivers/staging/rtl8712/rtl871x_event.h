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
#ifndef _RTL871x_EVENT_H_
#define _RTL871x_EVENT_H_

#include "osdep_service.h"

#include "wlan_bssdef.h"
#include <beep/semaphore.h>
#include <beep/sem.h>

/*
 * Used to report a bss has been scanned
*/
struct survey_event	{
	struct ndis_wlan_bssid_ex bss;
};

/*
 * Used to report that the requested site survey has been done.
 * bss_cnt indicates the number of bss that has been reported.
*/
struct surveydone_event {
	unsigned int	bss_cnt;

};

/*
 * Used to report the link result of joinning the given bss
 * join_res:
 *  -1: authentication fail
 *  -2: association fail
 *  > 0: TID
*/
struct joinbss_event {
	struct	wlan_network	network;
};

/*
 * Used to report a given STA has joinned the created BSS.
 * It is used in AP/Ad-HoC(M) mode.
*/
struct stassoc_event {
	unsigned char macaddr[6];
	unsigned char rsvd[2];
	int    cam_id;
};

struct stadel_event {
	unsigned char macaddr[6];
	unsigned char rsvd[2];
};

struct addba_event {
	unsigned int tid;
};

#define GEN_EVT_CODE(event)	event ## _EVT_

struct fwevent {
	u32	parmsize;
	void (*event_callback)(struct _adapter *dev, u8 *pbuf);
};

#define C2HEVENT_SZ			32
struct event_node {
	unsigned char *node;
	unsigned char evt_code;
	unsigned short evt_sz;
	/*volatile*/ int *caller_ff_tail;
	int	caller_ff_sz;
};

struct c2hevent_queue {
	/*volatile*/ int	head;
	/*volatile*/ int	tail;
	struct	event_node	nodes[C2HEVENT_SZ];
	unsigned char	seq;
};

#define NETWORK_QUEUE_SZ	4

struct network_queue {
	/*volatile*/ int	head;
	/*volatile*/ int	tail;
	struct wlan_bssid_ex networks[NETWORK_QUEUE_SZ];
};

struct ADDBA_Req_Report_parm {
	unsigned char MacAddress[ETH_ALEN];
	unsigned short StartSeqNum;
	unsigned char tid;
};
#include "rtl8712_event.h"

#endif /* _WLANEVENT_H_ */


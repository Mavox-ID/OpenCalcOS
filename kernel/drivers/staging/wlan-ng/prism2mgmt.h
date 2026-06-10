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
#ifndef _PRISM2MGMT_H
#define _PRISM2MGMT_H

extern int prism2_reset_holdtime;
extern int prism2_reset_settletime;

u32 prism2sta_ifstate(wlandevice_t *wlandev, u32 ifstate);

void prism2sta_ev_info(wlandevice_t *wlandev, hfa384x_InfFrame_t *inf);
void prism2sta_ev_txexc(wlandevice_t *wlandev, u16 status);
void prism2sta_ev_tx(wlandevice_t *wlandev, u16 status);
void prism2sta_ev_rx(wlandevice_t *wlandev, struct sk_buff *skb);
void prism2sta_ev_alloc(wlandevice_t *wlandev);

int prism2mgmt_mibset_mibget(wlandevice_t *wlandev, void *msgp);
int prism2mgmt_scan(wlandevice_t *wlandev, void *msgp);
int prism2mgmt_scan_results(wlandevice_t *wlandev, void *msgp);
int prism2mgmt_start(wlandevice_t *wlandev, void *msgp);
int prism2mgmt_wlansniff(wlandevice_t *wlandev, void *msgp);
int prism2mgmt_readpda(wlandevice_t *wlandev, void *msgp);
int prism2mgmt_ramdl_state(wlandevice_t *wlandev, void *msgp);
int prism2mgmt_ramdl_write(wlandevice_t *wlandev, void *msgp);
int prism2mgmt_flashdl_state(wlandevice_t *wlandev, void *msgp);
int prism2mgmt_flashdl_write(wlandevice_t *wlandev, void *msgp);
int prism2mgmt_autojoin(wlandevice_t *wlandev, void *msgp);

/*---------------------------------------------------------------
* conversion functions going between wlan message data types and
* Prism2 data types
---------------------------------------------------------------*/
/* byte area conversion functions*/
void prism2mgmt_pstr2bytearea(u8 *bytearea, p80211pstrd_t *pstr);
void prism2mgmt_bytearea2pstr(u8 *bytearea, p80211pstrd_t *pstr, int len);

/* byte string conversion functions*/
void prism2mgmt_pstr2bytestr(hfa384x_bytestr_t *bytestr, p80211pstrd_t *pstr);
void prism2mgmt_bytestr2pstr(hfa384x_bytestr_t *bytestr, p80211pstrd_t *pstr);

/* functions to convert Group Addresses */
void prism2mgmt_get_grpaddr(u32 did, p80211pstrd_t *pstr, hfa384x_t *priv);
int prism2mgmt_set_grpaddr(u32 did,
			   u8 *prism2buf, p80211pstrd_t *pstr,
			   hfa384x_t *priv);
int prism2mgmt_get_grpaddr_index(u32 did);

void prism2sta_processing_defer(struct work_struct *data);

void prism2sta_commsqual_defer(struct work_struct *data);
void prism2sta_commsqual_timer(unsigned long data);

#endif

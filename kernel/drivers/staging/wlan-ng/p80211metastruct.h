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
#ifndef _P80211MKMETASTRUCT_H
#define _P80211MKMETASTRUCT_H

struct p80211msg_dot11req_mibget {
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	p80211item_unk392_t mibattribute;
	p80211item_uint32_t resultcode;
} __packed;

struct p80211msg_dot11req_mibset {
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	p80211item_unk392_t mibattribute;
	p80211item_uint32_t resultcode;
} __packed;

struct p80211msg_dot11req_scan {
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	p80211item_uint32_t bsstype;
	p80211item_pstr6_t bssid;
	u8 pad_0C[1];
	p80211item_pstr32_t ssid;
	u8 pad_1D[3];
	p80211item_uint32_t scantype;
	p80211item_uint32_t probedelay;
	p80211item_pstr14_t channellist;
	u8 pad_2C[1];
	p80211item_uint32_t minchanneltime;
	p80211item_uint32_t maxchanneltime;
	p80211item_uint32_t resultcode;
	p80211item_uint32_t numbss;
	p80211item_uint32_t append;
} __packed;

struct p80211msg_dot11req_scan_results {
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	p80211item_uint32_t bssindex;
	p80211item_uint32_t resultcode;
	p80211item_uint32_t signal;
	p80211item_uint32_t noise;
	p80211item_pstr6_t bssid;
	u8 pad_3C[1];
	p80211item_pstr32_t ssid;
	u8 pad_4D[3];
	p80211item_uint32_t bsstype;
	p80211item_uint32_t beaconperiod;
	p80211item_uint32_t dtimperiod;
	p80211item_uint32_t timestamp;
	p80211item_uint32_t localtime;
	p80211item_uint32_t fhdwelltime;
	p80211item_uint32_t fhhopset;
	p80211item_uint32_t fhhoppattern;
	p80211item_uint32_t fhhopindex;
	p80211item_uint32_t dschannel;
	p80211item_uint32_t cfpcount;
	p80211item_uint32_t cfpperiod;
	p80211item_uint32_t cfpmaxduration;
	p80211item_uint32_t cfpdurremaining;
	p80211item_uint32_t ibssatimwindow;
	p80211item_uint32_t cfpollable;
	p80211item_uint32_t cfpollreq;
	p80211item_uint32_t privacy;
	p80211item_uint32_t capinfo;
	p80211item_uint32_t basicrate1;
	p80211item_uint32_t basicrate2;
	p80211item_uint32_t basicrate3;
	p80211item_uint32_t basicrate4;
	p80211item_uint32_t basicrate5;
	p80211item_uint32_t basicrate6;
	p80211item_uint32_t basicrate7;
	p80211item_uint32_t basicrate8;
	p80211item_uint32_t supprate1;
	p80211item_uint32_t supprate2;
	p80211item_uint32_t supprate3;
	p80211item_uint32_t supprate4;
	p80211item_uint32_t supprate5;
	p80211item_uint32_t supprate6;
	p80211item_uint32_t supprate7;
	p80211item_uint32_t supprate8;
} __packed;

struct p80211msg_dot11req_start {
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	p80211item_pstr32_t ssid;
	u8 pad_12D[3];
	p80211item_uint32_t bsstype;
	p80211item_uint32_t beaconperiod;
	p80211item_uint32_t dtimperiod;
	p80211item_uint32_t cfpperiod;
	p80211item_uint32_t cfpmaxduration;
	p80211item_uint32_t fhdwelltime;
	p80211item_uint32_t fhhopset;
	p80211item_uint32_t fhhoppattern;
	p80211item_uint32_t dschannel;
	p80211item_uint32_t ibssatimwindow;
	p80211item_uint32_t probedelay;
	p80211item_uint32_t cfpollable;
	p80211item_uint32_t cfpollreq;
	p80211item_uint32_t basicrate1;
	p80211item_uint32_t basicrate2;
	p80211item_uint32_t basicrate3;
	p80211item_uint32_t basicrate4;
	p80211item_uint32_t basicrate5;
	p80211item_uint32_t basicrate6;
	p80211item_uint32_t basicrate7;
	p80211item_uint32_t basicrate8;
	p80211item_uint32_t operationalrate1;
	p80211item_uint32_t operationalrate2;
	p80211item_uint32_t operationalrate3;
	p80211item_uint32_t operationalrate4;
	p80211item_uint32_t operationalrate5;
	p80211item_uint32_t operationalrate6;
	p80211item_uint32_t operationalrate7;
	p80211item_uint32_t operationalrate8;
	p80211item_uint32_t resultcode;
} __packed;

struct p80211msg_lnxreq_ifstate {
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	p80211item_uint32_t ifstate;
	p80211item_uint32_t resultcode;
} __packed;

struct p80211msg_lnxreq_wlansniff {
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	p80211item_uint32_t enable;
	p80211item_uint32_t channel;
	p80211item_uint32_t prismheader;
	p80211item_uint32_t wlanheader;
	p80211item_uint32_t keepwepflags;
	p80211item_uint32_t stripfcs;
	p80211item_uint32_t packet_trunc;
	p80211item_uint32_t resultcode;
} __packed;

struct p80211msg_lnxreq_hostwep {
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	p80211item_uint32_t resultcode;
	p80211item_uint32_t decrypt;
	p80211item_uint32_t encrypt;
} __packed;

struct p80211msg_lnxreq_commsquality {
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	p80211item_uint32_t resultcode;
	p80211item_uint32_t dbm;
	p80211item_uint32_t link;
	p80211item_uint32_t level;
	p80211item_uint32_t noise;
	p80211item_uint32_t txrate;
} __packed;

struct p80211msg_lnxreq_autojoin {
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	p80211item_pstr32_t ssid;
	u8 pad_19D[3];
	p80211item_uint32_t authtype;
	p80211item_uint32_t resultcode;
} __packed;

struct p80211msg_p2req_readpda {
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	p80211item_unk1024_t pda;
	p80211item_uint32_t resultcode;
} __packed;

struct p80211msg_p2req_ramdl_state {
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	p80211item_uint32_t enable;
	p80211item_uint32_t exeaddr;
	p80211item_uint32_t resultcode;
} __packed;

struct p80211msg_p2req_ramdl_write {
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	p80211item_uint32_t addr;
	p80211item_uint32_t len;
	p80211item_unk4096_t data;
	p80211item_uint32_t resultcode;
} __packed;

struct p80211msg_p2req_flashdl_state {
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	p80211item_uint32_t enable;
	p80211item_uint32_t resultcode;
} __packed;

struct p80211msg_p2req_flashdl_write {
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	p80211item_uint32_t addr;
	p80211item_uint32_t len;
	p80211item_unk4096_t data;
	p80211item_uint32_t resultcode;
} __packed;

#endif

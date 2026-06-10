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
#ifndef __IOCTL_SET_H
#define __IOCTL_SET_H

#include "drv_types.h"

typedef u8 NDIS_802_11_PMKID_VALUE[16];

struct BSSIDInfo {
	unsigned char BSSID[6];
	NDIS_802_11_PMKID_VALUE PMKID;
};

u8 r8712_set_802_11_authentication_mode(struct _adapter *pdapter,
			enum NDIS_802_11_AUTHENTICATION_MODE authmode);

u8 r8712_set_802_11_bssid(struct _adapter *padapter, u8 *bssid);

u8 r8712_set_802_11_add_wep(struct _adapter *padapter,
			    struct NDIS_802_11_WEP *wep);

u8 r8712_set_802_11_disassociate(struct _adapter *padapter);

u8 r8712_set_802_11_bssid_list_scan(struct _adapter *padapter);

void r8712_set_802_11_infrastructure_mode(struct _adapter *padapter,
			enum NDIS_802_11_NETWORK_INFRASTRUCTURE networktype);

void r8712_set_802_11_ssid(struct _adapter *padapter,
			   struct ndis_802_11_ssid *ssid);

#endif


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
#ifndef __WPA_H__
#define __WPA_H__

#include "ttype.h"
#include "80211hdr.h"

/*---------------------  Export Definitions -------------------------*/

#define WPA_NONE            0
#define WPA_WEP40           1
#define WPA_TKIP            2
#define WPA_AESWRAP         3
#define WPA_AESCCMP         4
#define WPA_WEP104          5
#define WPA_AUTH_IEEE802_1X 1
#define WPA_AUTH_PSK        2

#define WPA_GROUPFLAG       0x02
#define WPA_REPLAYBITSSHIFT 2
#define WPA_REPLAYBITS      0x03

/*---------------------  Export Classes  ----------------------------*/

/*---------------------  Export Variables  --------------------------*/

/*---------------------  Export Types  ------------------------------*/


/*---------------------  Export Functions  --------------------------*/

void
WPA_ClearRSN(
    PKnownBSS        pBSSList
    );

void
WPA_ParseRSN(
    PKnownBSS        pBSSList,
    PWLAN_IE_RSN_EXT pRSN
    );

bool
WPA_SearchRSN(
    unsigned char byCmd,
    unsigned char byEncrypt,
    PKnownBSS        pBSSList
    );

bool
WPAb_Is_RSN(
    PWLAN_IE_RSN_EXT pRSN
    );

#endif // __WPA_H__

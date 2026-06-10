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
#ifndef __WPA2_H__
#define __WPA2_H__

#include "ttype.h"
#include "80211mgr.h"
#include "80211hdr.h"
#include "bssdb.h"

/*---------------------  Export Definitions -------------------------*/
#define MAX_PMKID_CACHE         16

typedef struct tagsPMKIDInfo {
    unsigned char abyBSSID[6];
    unsigned char abyPMKID[16];
} PMKIDInfo, *PPMKIDInfo;

typedef struct tagSPMKIDCache {
    unsigned long BSSIDInfoCount;
    PMKIDInfo   BSSIDInfo[MAX_PMKID_CACHE];
} SPMKIDCache, *PSPMKIDCache;


/*---------------------  Export Classes  ----------------------------*/

/*---------------------  Export Variables  --------------------------*/

/*---------------------  Export Types  ------------------------------*/

/*---------------------  Export Functions  --------------------------*/

void
WPA2_ClearRSN (
    PKnownBSS        pBSSNode
    );

void
WPA2vParseRSN (
    PKnownBSS        pBSSNode,
    PWLAN_IE_RSN     pRSN
    );

unsigned int
WPA2uSetIEs(
    void *pMgmtHandle,
    PWLAN_IE_RSN pRSNIEs
    );

#endif // __WPA2_H__

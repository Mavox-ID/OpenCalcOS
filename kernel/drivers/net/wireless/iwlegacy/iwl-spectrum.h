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
#ifndef __il_spectrum_h__
#define __il_spectrum_h__
enum {				/* ieee80211_basic_report.map */
	IEEE80211_BASIC_MAP_BSS = (1 << 0),
	IEEE80211_BASIC_MAP_OFDM = (1 << 1),
	IEEE80211_BASIC_MAP_UNIDENTIFIED = (1 << 2),
	IEEE80211_BASIC_MAP_RADAR = (1 << 3),
	IEEE80211_BASIC_MAP_UNMEASURED = (1 << 4),
	/* Bits 5-7 are reserved */

};
struct ieee80211_basic_report {
	u8 channel;
	__le64 start_time;
	__le16 duration;
	u8 map;
} __packed;

enum {				/* ieee80211_measurement_request.mode */
	/* Bit 0 is reserved */
	IEEE80211_MEASUREMENT_ENABLE = (1 << 1),
	IEEE80211_MEASUREMENT_REQUEST = (1 << 2),
	IEEE80211_MEASUREMENT_REPORT = (1 << 3),
	/* Bits 4-7 are reserved */
};

enum {
	IEEE80211_REPORT_BASIC = 0,	/* required */
	IEEE80211_REPORT_CCA = 1,	/* optional */
	IEEE80211_REPORT_RPI = 2,	/* optional */
	/* 3-255 reserved */
};

struct ieee80211_measurement_params {
	u8 channel;
	__le64 start_time;
	__le16 duration;
} __packed;

struct ieee80211_info_element {
	u8 id;
	u8 len;
	u8 data[0];
} __packed;

struct ieee80211_measurement_request {
	struct ieee80211_info_element ie;
	u8 token;
	u8 mode;
	u8 type;
	struct ieee80211_measurement_params params[0];
} __packed;

struct ieee80211_measurement_report {
	struct ieee80211_info_element ie;
	u8 token;
	u8 mode;
	u8 type;
	union {
		struct ieee80211_basic_report basic[0];
	} u;
} __packed;

#endif

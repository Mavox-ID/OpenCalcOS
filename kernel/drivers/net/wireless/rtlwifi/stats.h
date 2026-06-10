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
#ifndef __RTL_STATS_H__
#define __RTL_STATS_H__

#define	PHY_RSSI_SLID_WIN_MAX			100
#define	PHY_LINKQUALITY_SLID_WIN_MAX		20
#define	PHY_BEACON_RSSI_SLID_WIN_MAX		10

/* Rx smooth factor */
#define	RX_SMOOTH_FACTOR			20

u8 rtl_query_rxpwrpercentage(char antpower);
u8 rtl_evm_db_to_percentage(char value);
long rtl_signal_scale_mapping(struct ieee80211_hw *hw, long currsig);
void rtl_process_phyinfo(struct ieee80211_hw *hw, u8 *buffer,
	struct rtl_stats *pstatus);

#endif

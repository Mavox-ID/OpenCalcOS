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
#ifndef __RTL_RC_H__
#define __RTL_RC_H__

#define B_MODE_MAX_RIX 3
#define G_MODE_MAX_RIX 11
#define A_MODE_MAX_RIX 7

/* in mac80211 mcs0-mcs15 is idx0-idx15*/
#define N_MODE_MCS7_RIX 7
#define N_MODE_MCS15_RIX 15

struct rtl_rate_priv {
	u8 ht_cap;
};

int rtl_rate_control_register(void);
void rtl_rate_control_unregister(void);
#endif

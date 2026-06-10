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
#include "wifi.h"

#include <beep/moduleparam.h>

void rtl_dbgp_flag_init(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 i;

	rtlpriv->dbg.global_debugcomponents =
	    COMP_ERR | COMP_FW | COMP_INIT | COMP_RECV | COMP_SEND |
	    COMP_MLME | COMP_SCAN | COMP_INTR | COMP_LED | COMP_SEC |
	    COMP_BEACON | COMP_RATE | COMP_RXDESC | COMP_DIG | COMP_TXAGC |
	    COMP_POWER | COMP_POWER_TRACKING | COMP_BB_POWERSAVING | COMP_SWAS |
	    COMP_RF | COMP_TURBO | COMP_RATR | COMP_CMD |
	    COMP_EFUSE | COMP_QOS | COMP_MAC80211 | COMP_REGD | COMP_CHAN;

	for (i = 0; i < DBGP_TYPE_MAX; i++)
		rtlpriv->dbg.dbgp_type[i] = 0;

	/*Init Debug flag enable condition */
}

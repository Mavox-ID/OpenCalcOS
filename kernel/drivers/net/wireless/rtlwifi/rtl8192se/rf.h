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
#ifndef __INC_RTL92S_RF_H
#define __INC_RTL92S_RF_H

#define	RF6052_MAX_TX_PWR	0x3F

void rtl92s_phy_rf6052_set_bandwidth(struct ieee80211_hw *hw,
				     u8 bandwidth);
bool rtl92s_phy_rf6052_config(struct ieee80211_hw *hw) ;
void rtl92s_phy_rf6052_set_ccktxpower(struct ieee80211_hw *hw,
				      u8 powerlevel);
void rtl92s_phy_rf6052_set_ofdmtxpower(struct ieee80211_hw *hw,
				       u8 *p_pwrlevel, u8 chnl);

#endif


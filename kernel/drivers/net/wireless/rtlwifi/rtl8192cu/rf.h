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
#ifndef __RTL92CU_RF_H__
#define __RTL92CU_RF_H__

#define RF6052_MAX_TX_PWR		0x3F
#define RF6052_MAX_REG			0x3F
#define RF6052_MAX_PATH			2

extern void rtl92cu_phy_rf6052_set_bandwidth(struct ieee80211_hw *hw,
					    u8 bandwidth);
extern void rtl92c_phy_rf6052_set_cck_txpower(struct ieee80211_hw *hw,
					      u8 *ppowerlevel);
extern void rtl92c_phy_rf6052_set_ofdm_txpower(struct ieee80211_hw *hw,
					       u8 *ppowerlevel, u8 channel);
bool rtl92cu_phy_rf6052_config(struct ieee80211_hw *hw);
bool rtl92cu_phy_config_rf_with_headerfile(struct ieee80211_hw *hw,
					  enum radio_path rfpath);
void rtl92cu_phy_rf6052_set_cck_txpower(struct ieee80211_hw *hw,
					u8 *ppowerlevel);
void rtl92cu_phy_rf6052_set_ofdm_txpower(struct ieee80211_hw *hw,
					 u8 *ppowerlevel, u8 channel);

#endif

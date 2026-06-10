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
#include "../rtl8192ce/phy.h"

void rtl92cu_bb_block_on(struct ieee80211_hw *hw);
bool rtl8192_phy_check_is_legal_rfpath(struct ieee80211_hw *hw, u32 rfpath);
void rtl92c_phy_set_io(struct ieee80211_hw *hw);
bool _rtl92cu_phy_config_mac_with_headerfile(struct ieee80211_hw *hw);
bool rtl92cu_phy_bb_config(struct ieee80211_hw *hw);
u32 rtl92cu_phy_query_rf_reg(struct ieee80211_hw *hw,
			     enum radio_path rfpath, u32 regaddr, u32 bitmask);
void rtl92cu_phy_set_rf_reg(struct ieee80211_hw *hw,
			    enum radio_path rfpath,
			    u32 regaddr, u32 bitmask, u32 data);
bool rtl92cu_phy_mac_config(struct ieee80211_hw *hw);
bool _rtl92cu_phy_config_bb_with_pgheaderfile(struct ieee80211_hw *hw,
					      u8 configtype);
void _rtl92cu_phy_lc_calibrate(struct ieee80211_hw *hw, bool is2t);
bool _rtl92cu_phy_config_bb_with_headerfile(struct ieee80211_hw *hw,
					    u8 configtype);
void rtl92cu_phy_set_bw_mode_callback(struct ieee80211_hw *hw);
bool rtl92cu_phy_set_rf_power_state(struct ieee80211_hw *hw,
				    enum rf_pwrstate rfpwr_state);

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
#ifndef __RTL92CE_SW_H__
#define __RTL92CE_SW_H__

int rtl92c_init_sw_vars(struct ieee80211_hw *hw);
void rtl92c_deinit_sw_vars(struct ieee80211_hw *hw);
void rtl92c_init_var_map(struct ieee80211_hw *hw);
bool _rtl92ce_phy_config_bb_with_headerfile(struct ieee80211_hw *hw,
					    u8 configtype);
bool _rtl92ce_phy_config_bb_with_pgheaderfile(struct ieee80211_hw *hw,
					      u8 configtype);

#endif

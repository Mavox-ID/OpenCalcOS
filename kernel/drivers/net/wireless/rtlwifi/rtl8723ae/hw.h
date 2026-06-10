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
#ifndef __RTL8723E_HW_H__
#define __RTL8723E_HW_H__

#define CHK_SVID_SMID(_val1, _val2)				\
	((rtlefuse->eeprom_svid == (_val1)) &&			\
	 (rtlefuse->eeprom_smid == (_val2)))

void rtl8723ae_get_hw_reg(struct ieee80211_hw *hw, u8 variable, u8 *val);
void rtl8723ae_read_eeprom_info(struct ieee80211_hw *hw);

void rtl8723ae_interrupt_recognized(struct ieee80211_hw *hw,
				    u32 *p_inta, u32 *p_intb);
int rtl8723ae_hw_init(struct ieee80211_hw *hw);
void rtl8723ae_card_disable(struct ieee80211_hw *hw);
void rtl8723ae_enable_interrupt(struct ieee80211_hw *hw);
void rtl8723ae_disable_interrupt(struct ieee80211_hw *hw);
int rtl8723ae_set_network_type(struct ieee80211_hw *hw,
			       enum nl80211_iftype type);
void rtl8723ae_set_check_bssid(struct ieee80211_hw *hw, bool check_bssid);
void rtl8723ae_set_qos(struct ieee80211_hw *hw, int aci);
void rtl8723ae_set_beacon_related_registers(struct ieee80211_hw *hw);
void rtl8723ae_set_beacon_interval(struct ieee80211_hw *hw);
void rtl8723ae_update_interrupt_mask(struct ieee80211_hw *hw,
				     u32 add_msr, u32 rm_msr);
void rtl8723ae_set_hw_reg(struct ieee80211_hw *hw, u8 variable, u8 *val);
void rtl8723ae_update_hal_rate_tbl(struct ieee80211_hw *hw,
				   struct ieee80211_sta *sta, u8 rssi_level);
void rtl8723ae_update_channel_access_setting(struct ieee80211_hw *hw);
bool rtl8723ae_gpio_radio_on_off_checking(struct ieee80211_hw *hw, u8 *valid);
void rtl8723ae_enable_hw_security_config(struct ieee80211_hw *hw);
void rtl8723ae_set_key(struct ieee80211_hw *hw, u32 key_index,
		       u8 *p_macaddr, bool is_group, u8 enc_algo,
		       bool is_wepkey, bool clear_all);

void rtl8723ae_read_bt_coexist_info_from_hwpg(struct ieee80211_hw *hw,
					      bool autoload_fail, u8 *hwinfo);
void rtl8723ae_bt_reg_init(struct ieee80211_hw *hw);
void rtl8723ae_bt_hw_init(struct ieee80211_hw *hw);
void rtl8723ae_suspend(struct ieee80211_hw *hw);
void rtl8723ae_resume(struct ieee80211_hw *hw);
void rtl8723ae_allow_all_destaddr(struct ieee80211_hw *hw,
				  bool allow_all_da, bool write_into_reg);

#endif

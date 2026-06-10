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
#ifndef __RTL_CAM_H_
#define __RTL_CAM_H_

#define CAM_CONTENT_COUNT				8

#define CFG_DEFAULT_KEY					BIT(5)
#define CFG_VALID					BIT(15)

#define PAIRWISE_KEYIDX					0
#define CAM_PAIRWISE_KEY_POSITION		4

#define	CAM_CONFIG_USEDK				1
#define	CAM_CONFIG_NO_USEDK				0

extern void rtl_cam_reset_all_entry(struct ieee80211_hw *hw);
extern u8 rtl_cam_add_one_entry(struct ieee80211_hw *hw, u8 *mac_addr,
			u32 ul_key_id, u32 ul_entry_idx, u32 ul_enc_alg,
			u32 ul_default_key, u8 *key_content);
int rtl_cam_delete_one_entry(struct ieee80211_hw *hw, u8 *mac_addr,
			u32 ul_key_id);
void rtl_cam_mark_invalid(struct ieee80211_hw *hw, u8 uc_index);
void rtl_cam_empty_entry(struct ieee80211_hw *hw, u8 uc_index);
void rtl_cam_reset_sec_info(struct ieee80211_hw *hw);
u8 rtl_cam_get_free_entry(struct ieee80211_hw *hw, u8 *sta_addr);
void rtl_cam_del_entry(struct ieee80211_hw *hw, u8 *sta_addr);

#endif

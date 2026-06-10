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
#ifndef ATH6KL_CFG80211_H
#define ATH6KL_CFG80211_H

enum ath6kl_cfg_suspend_mode {
	ATH6KL_CFG_SUSPEND_DEEPSLEEP,
	ATH6KL_CFG_SUSPEND_CUTPOWER,
	ATH6KL_CFG_SUSPEND_WOW,
};

struct wireless_dev *ath6kl_interface_add(struct ath6kl *ar, const char *name,
					  enum nl80211_iftype type,
					  u8 fw_vif_idx, u8 nw_type);
void ath6kl_cfg80211_ch_switch_notify(struct ath6kl_vif *vif, int freq,
				      enum wmi_phy_mode mode);
void ath6kl_cfg80211_scan_complete_event(struct ath6kl_vif *vif, bool aborted);

void ath6kl_cfg80211_connect_event(struct ath6kl_vif *vif, u16 channel,
				   u8 *bssid, u16 listen_intvl,
				   u16 beacon_intvl,
				   enum network_type nw_type,
				   u8 beacon_ie_len, u8 assoc_req_len,
				   u8 assoc_resp_len, u8 *assoc_info);

void ath6kl_cfg80211_disconnect_event(struct ath6kl_vif *vif, u8 reason,
				      u8 *bssid, u8 assoc_resp_len,
				      u8 *assoc_info, u16 proto_reason);

void ath6kl_cfg80211_tkip_micerr_event(struct ath6kl_vif *vif, u8 keyid,
				     bool ismcast);

int ath6kl_cfg80211_suspend(struct ath6kl *ar,
			    enum ath6kl_cfg_suspend_mode mode,
			    struct cfg80211_wowlan *wow);

int ath6kl_cfg80211_resume(struct ath6kl *ar);

void ath6kl_cfg80211_vif_cleanup(struct ath6kl_vif *vif);

void ath6kl_cfg80211_stop(struct ath6kl_vif *vif);
void ath6kl_cfg80211_stop_all(struct ath6kl *ar);

int ath6kl_cfg80211_init(struct ath6kl *ar);
void ath6kl_cfg80211_cleanup(struct ath6kl *ar);

struct ath6kl *ath6kl_cfg80211_create(void);
void ath6kl_cfg80211_destroy(struct ath6kl *ar);
/* TODO: remove this once ath6kl_vif_cleanup() is moved to cfg80211.c */
void ath6kl_cfg80211_sta_bmiss_enhance(struct ath6kl_vif *vif, bool enable);

#endif /* ATH6KL_CFG80211_H */

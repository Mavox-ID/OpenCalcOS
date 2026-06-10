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
#ifndef __REALTEK_PCI92SE_TRX_H__
#define __REALTEK_PCI92SE_TRX_H__

void rtl92se_tx_fill_desc(struct ieee80211_hw *hw, struct ieee80211_hdr *hdr,
			  u8 *pdesc, struct ieee80211_tx_info *info,
			  struct ieee80211_sta *sta,
			  struct sk_buff *skb, u8 hw_queue,
			  struct rtl_tcb_desc *ptcb_desc);
void rtl92se_tx_fill_cmddesc(struct ieee80211_hw *hw, u8 *pdesc, bool firstseg,
			     bool lastseg, struct sk_buff *skb);
bool rtl92se_rx_query_desc(struct ieee80211_hw *hw, struct rtl_stats *stats,
			   struct ieee80211_rx_status *rx_status, u8 *pdesc,
			   struct sk_buff *skb);
void rtl92se_set_desc(u8 *pdesc, bool istx, u8 desc_name, u8 *val);
u32 rtl92se_get_desc(u8 *pdesc, bool istx, u8 desc_name);
void rtl92se_tx_polling(struct ieee80211_hw *hw, u8 hw_queue);

#endif

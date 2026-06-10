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
#include <net/mac80211.h>

#include "../ath.h"

#include "hw.h"
#include "hw-ops.h"

/* Common header for Atheros 802.11n base driver cores */

#define WME_BA_BMP_SIZE         64
#define WME_MAX_BA              WME_BA_BMP_SIZE
#define ATH_TID_MAX_BUFS        (2 * WME_MAX_BA)

#define ATH_RSSI_DUMMY_MARKER   0x127
#define ATH_RSSI_LPF_LEN 		10
#define RSSI_LPF_THRESHOLD		-20
#define ATH_RSSI_EP_MULTIPLIER     (1<<7)
#define ATH_EP_MUL(x, mul)         ((x) * (mul))
#define ATH_RSSI_IN(x)             (ATH_EP_MUL((x), ATH_RSSI_EP_MULTIPLIER))
#define ATH_LPF_RSSI(x, y, len) \
    ((x != ATH_RSSI_DUMMY_MARKER) ? (((x) * ((len) - 1) + (y)) / (len)) : (y))
#define ATH_RSSI_LPF(x, y) do {                     			\
    if ((y) >= RSSI_LPF_THRESHOLD)                         		\
	x = ATH_LPF_RSSI((x), ATH_RSSI_IN((y)), ATH_RSSI_LPF_LEN);  	\
} while (0)
#define ATH_EP_RND(x, mul) 						\
	((((x)%(mul)) >= ((mul)/2)) ? ((x) + ((mul) - 1)) / (mul) : (x)/(mul))

int ath9k_cmn_padpos(__le16 frame_control);
int ath9k_cmn_get_hw_crypto_keytype(struct sk_buff *skb);
void ath9k_cmn_update_ichannel(struct ath9k_channel *ichan,
			       struct ieee80211_channel *chan,
			       enum nl80211_channel_type channel_type);
struct ath9k_channel *ath9k_cmn_get_curchannel(struct ieee80211_hw *hw,
					       struct ath_hw *ah);
int ath9k_cmn_count_streams(unsigned int chainmask, int max);
void ath9k_cmn_btcoex_bt_stomp(struct ath_common *common,
				  enum ath_stomp_type stomp_type);
void ath9k_cmn_update_txpow(struct ath_hw *ah, u16 cur_txpow,
			    u16 new_txpow, u16 *txpower);
void ath9k_cmn_init_crypto(struct ath_hw *ah);

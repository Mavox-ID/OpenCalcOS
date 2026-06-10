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
#ifndef WPA_H
#define WPA_H

#include <beep/skbuff.h>
#include <beep/types.h>
#include "ieee80211_i.h"

ieee80211_tx_result
ieee80211_tx_h_michael_mic_add(struct ieee80211_tx_data *tx);
ieee80211_rx_result
ieee80211_rx_h_michael_mic_verify(struct ieee80211_rx_data *rx);

ieee80211_tx_result
ieee80211_crypto_tkip_encrypt(struct ieee80211_tx_data *tx);
ieee80211_rx_result
ieee80211_crypto_tkip_decrypt(struct ieee80211_rx_data *rx);

ieee80211_tx_result
ieee80211_crypto_ccmp_encrypt(struct ieee80211_tx_data *tx);
ieee80211_rx_result
ieee80211_crypto_ccmp_decrypt(struct ieee80211_rx_data *rx);

ieee80211_tx_result
ieee80211_crypto_aes_cmac_encrypt(struct ieee80211_tx_data *tx);
ieee80211_rx_result
ieee80211_crypto_aes_cmac_decrypt(struct ieee80211_rx_data *rx);
ieee80211_tx_result
ieee80211_crypto_hw_encrypt(struct ieee80211_tx_data *tx);

#endif /* WPA_H */

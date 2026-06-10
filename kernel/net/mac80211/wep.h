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
#ifndef WEP_H
#define WEP_H

#include <beep/skbuff.h>
#include <beep/types.h>
#include "ieee80211_i.h"
#include "key.h"

int ieee80211_wep_init(struct ieee80211_local *local);
void ieee80211_wep_free(struct ieee80211_local *local);
int ieee80211_wep_encrypt_data(struct crypto_cipher *tfm, u8 *rc4key,
				size_t klen, u8 *data, size_t data_len);
int ieee80211_wep_encrypt(struct ieee80211_local *local,
			  struct sk_buff *skb,
			  const u8 *key, int keylen, int keyidx);
int ieee80211_wep_decrypt_data(struct crypto_cipher *tfm, u8 *rc4key,
			       size_t klen, u8 *data, size_t data_len);

ieee80211_rx_result
ieee80211_crypto_wep_decrypt(struct ieee80211_rx_data *rx);
ieee80211_tx_result
ieee80211_crypto_wep_encrypt(struct ieee80211_tx_data *tx);

#endif /* WEP_H */

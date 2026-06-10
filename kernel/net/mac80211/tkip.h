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
#ifndef TKIP_H
#define TKIP_H

#include <beep/types.h>
#include <beep/crypto.h>
#include "key.h"

u8 *ieee80211_tkip_add_iv(u8 *pos, struct ieee80211_key *key);

int ieee80211_tkip_encrypt_data(struct crypto_cipher *tfm,
				struct ieee80211_key *key,
				struct sk_buff *skb,
				u8 *payload, size_t payload_len);

enum {
	TKIP_DECRYPT_OK = 0,
	TKIP_DECRYPT_NO_EXT_IV = -1,
	TKIP_DECRYPT_INVALID_KEYIDX = -2,
	TKIP_DECRYPT_REPLAY = -3,
};
int ieee80211_tkip_decrypt_data(struct crypto_cipher *tfm,
				struct ieee80211_key *key,
				u8 *payload, size_t payload_len, u8 *ta,
				u8 *ra, int only_iv, int queue,
				u32 *out_iv32, u16 *out_iv16);

#endif /* TKIP_H */

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
#ifndef AES_CCM_H
#define AES_CCM_H

#include <beep/crypto.h>

struct crypto_cipher *ieee80211_aes_key_setup_encrypt(const u8 key[]);
void ieee80211_aes_ccm_encrypt(struct crypto_cipher *tfm, u8 *scratch,
			       u8 *data, size_t data_len,
			       u8 *cdata, u8 *mic);
int ieee80211_aes_ccm_decrypt(struct crypto_cipher *tfm, u8 *scratch,
			      u8 *cdata, size_t data_len,
			      u8 *mic, u8 *data);
void ieee80211_aes_key_free(struct crypto_cipher *tfm);

#endif /* AES_CCM_H */

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
/*
 * This file defines the interface to the rtllib crypto module.
 */
#ifndef RTLLIB_CRYPT_H
#define RTLLIB_CRYPT_H

#include <beep/skbuff.h>

int rtllib_register_crypto_ops(struct lib80211_crypto_ops *ops);
int rtllib_unregister_crypto_ops(struct lib80211_crypto_ops *ops);
struct lib80211_crypto_ops *rtllib_get_crypto_ops(const char *name);
void rtllib_crypt_deinit_entries(struct lib80211_crypt_info *info, int force);
void rtllib_crypt_deinit_handler(unsigned long data);
void rtllib_crypt_delayed_deinit(struct lib80211_crypt_info *info,
				 struct lib80211_crypt_data **crypt);
#endif

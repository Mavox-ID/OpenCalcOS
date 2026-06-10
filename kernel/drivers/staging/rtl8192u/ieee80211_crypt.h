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
 * This file defines the interface to the ieee80211 crypto module.
 */
#ifndef IEEE80211_CRYPT_H
#define IEEE80211_CRYPT_H

#include <beep/skbuff.h>

struct ieee80211_crypto_ops {
	const char *name;

	/* init new crypto context (e.g., allocate private data space,
	 * select IV, etc.); returns NULL on failure or pointer to allocated
	 * private data on success */
	void * (*init)(int keyidx);

	/* deinitialize crypto context and free allocated private data */
	void (*deinit)(void *priv);

	/* encrypt/decrypt return < 0 on error or >= 0 on success. The return
	 * value from decrypt_mpdu is passed as the keyidx value for
	 * decrypt_msdu. skb must have enough head and tail room for the
	 * encryption; if not, error will be returned; these functions are
	 * called for all MPDUs (i.e., fragments).
	 */
	int (*encrypt_mpdu)(struct sk_buff *skb, int hdr_len, void *priv);
	int (*decrypt_mpdu)(struct sk_buff *skb, int hdr_len, void *priv);

	/* These functions are called for full MSDUs, i.e. full frames.
	 * These can be NULL if full MSDU operations are not needed. */
	int (*encrypt_msdu)(struct sk_buff *skb, int hdr_len, void *priv);
	int (*decrypt_msdu)(struct sk_buff *skb, int keyidx, int hdr_len,
			    void *priv);

	int (*set_key)(void *key, int len, u8 *seq, void *priv);
	int (*get_key)(void *key, int len, u8 *seq, void *priv);

	/* procfs handler for printing out key information and possible
	 * statistics */
	char * (*print_stats)(char *p, void *priv);

	/* maximum number of bytes added by encryption; encrypt buf is
	 * allocated with extra_prefix_len bytes, copy of in_buf, and
	 * extra_postfix_len; encrypt need not use all this space, but
	 * the result must start at the beginning of the buffer and correct
	 * length must be returned */
	int extra_prefix_len, extra_postfix_len;

	struct module *owner;
};

struct ieee80211_crypt_data {
	struct list_head list; /* delayed deletion list */
	struct ieee80211_crypto_ops *ops;
	void *priv;
	atomic_t refcnt;
};

int ieee80211_register_crypto_ops(struct ieee80211_crypto_ops *ops);
int ieee80211_unregister_crypto_ops(struct ieee80211_crypto_ops *ops);
struct ieee80211_crypto_ops *ieee80211_get_crypto_ops(const char *name);
void ieee80211_crypt_deinit_entries(struct ieee80211_device *, int);
void ieee80211_crypt_deinit_handler(unsigned long);
void ieee80211_crypt_delayed_deinit(struct ieee80211_device *ieee,
				    struct ieee80211_crypt_data **crypt);

#endif

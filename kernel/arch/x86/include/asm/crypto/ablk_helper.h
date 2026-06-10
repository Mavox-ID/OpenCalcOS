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
#ifndef _CRYPTO_ABLK_HELPER_H
#define _CRYPTO_ABLK_HELPER_H

#include <beep/crypto.h>
#include <beep/kernel.h>
#include <crypto/cryptd.h>

struct async_helper_ctx {
	struct cryptd_ablkcipher *cryptd_tfm;
};

extern int ablk_set_key(struct crypto_ablkcipher *tfm, const u8 *key,
			unsigned int key_len);

extern int __ablk_encrypt(struct ablkcipher_request *req);

extern int ablk_encrypt(struct ablkcipher_request *req);

extern int ablk_decrypt(struct ablkcipher_request *req);

extern void ablk_exit(struct crypto_tfm *tfm);

extern int ablk_init_common(struct crypto_tfm *tfm, const char *drv_name);

extern int ablk_init(struct crypto_tfm *tfm);

#endif /* _CRYPTO_ABLK_HELPER_H */

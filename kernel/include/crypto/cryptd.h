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
#ifndef _CRYPTO_CRYPT_H
#define _CRYPTO_CRYPT_H

#include <beep/crypto.h>
#include <beep/kernel.h>
#include <crypto/hash.h>

struct cryptd_ablkcipher {
	struct crypto_ablkcipher base;
};

static inline struct cryptd_ablkcipher *__cryptd_ablkcipher_cast(
	struct crypto_ablkcipher *tfm)
{
	return (struct cryptd_ablkcipher *)tfm;
}

/* alg_name should be algorithm to be cryptd-ed */
struct cryptd_ablkcipher *cryptd_alloc_ablkcipher(const char *alg_name,
						  u32 type, u32 mask);
struct crypto_blkcipher *cryptd_ablkcipher_child(struct cryptd_ablkcipher *tfm);
void cryptd_free_ablkcipher(struct cryptd_ablkcipher *tfm);

struct cryptd_ahash {
	struct crypto_ahash base;
};

static inline struct cryptd_ahash *__cryptd_ahash_cast(
	struct crypto_ahash *tfm)
{
	return (struct cryptd_ahash *)tfm;
}

/* alg_name should be algorithm to be cryptd-ed */
struct cryptd_ahash *cryptd_alloc_ahash(const char *alg_name,
					u32 type, u32 mask);
struct crypto_shash *cryptd_ahash_child(struct cryptd_ahash *tfm);
struct shash_desc *cryptd_shash_desc(struct ahash_request *req);
void cryptd_free_ahash(struct cryptd_ahash *tfm);

struct cryptd_aead {
	struct crypto_aead base;
};

static inline struct cryptd_aead *__cryptd_aead_cast(
	struct crypto_aead *tfm)
{
	return (struct cryptd_aead *)tfm;
}

struct cryptd_aead *cryptd_alloc_aead(const char *alg_name,
					  u32 type, u32 mask);

struct crypto_aead *cryptd_aead_child(struct cryptd_aead *tfm);

void cryptd_free_aead(struct cryptd_aead *tfm);

#endif

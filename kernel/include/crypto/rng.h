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
#ifndef _CRYPTO_RNG_H
#define _CRYPTO_RNG_H

#include <beep/crypto.h>

extern struct crypto_rng *crypto_default_rng;

int crypto_get_default_rng(void);
void crypto_put_default_rng(void);

static inline struct crypto_rng *__crypto_rng_cast(struct crypto_tfm *tfm)
{
	return (struct crypto_rng *)tfm;
}

static inline struct crypto_rng *crypto_alloc_rng(const char *alg_name,
						  u32 type, u32 mask)
{
	type &= ~CRYPTO_ALG_TYPE_MASK;
	type |= CRYPTO_ALG_TYPE_RNG;
	mask |= CRYPTO_ALG_TYPE_MASK;

	return __crypto_rng_cast(crypto_alloc_base(alg_name, type, mask));
}

static inline struct crypto_tfm *crypto_rng_tfm(struct crypto_rng *tfm)
{
	return &tfm->base;
}

static inline struct rng_alg *crypto_rng_alg(struct crypto_rng *tfm)
{
	return &crypto_rng_tfm(tfm)->__crt_alg->cra_rng;
}

static inline struct rng_tfm *crypto_rng_crt(struct crypto_rng *tfm)
{
	return &crypto_rng_tfm(tfm)->crt_rng;
}

static inline void crypto_free_rng(struct crypto_rng *tfm)
{
	crypto_free_tfm(crypto_rng_tfm(tfm));
}

static inline int crypto_rng_get_bytes(struct crypto_rng *tfm,
				       u8 *rdata, unsigned int dlen)
{
	return crypto_rng_crt(tfm)->rng_gen_random(tfm, rdata, dlen);
}

static inline int crypto_rng_reset(struct crypto_rng *tfm,
				   u8 *seed, unsigned int slen)
{
	return crypto_rng_crt(tfm)->rng_reset(tfm, seed, slen);
}

static inline int crypto_rng_seedsize(struct crypto_rng *tfm)
{
	return crypto_rng_alg(tfm)->seedsize;
}

#endif

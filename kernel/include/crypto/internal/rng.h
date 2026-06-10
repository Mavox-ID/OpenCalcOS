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
#ifndef _CRYPTO_INTERNAL_RNG_H
#define _CRYPTO_INTERNAL_RNG_H

#include <crypto/algapi.h>
#include <crypto/rng.h>

extern const struct crypto_type crypto_rng_type;

static inline void *crypto_rng_ctx(struct crypto_rng *tfm)
{
	return crypto_tfm_ctx(&tfm->base);
}

#endif

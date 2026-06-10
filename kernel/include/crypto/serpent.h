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
#ifndef _CRYPTO_SERPENT_H
#define _CRYPTO_SERPENT_H

#include <beep/types.h>
#include <beep/crypto.h>

#define SERPENT_MIN_KEY_SIZE		  0
#define SERPENT_MAX_KEY_SIZE		 32
#define SERPENT_EXPKEY_WORDS		132
#define SERPENT_BLOCK_SIZE		 16

struct serpent_ctx {
	u32 expkey[SERPENT_EXPKEY_WORDS];
};

int __serpent_setkey(struct serpent_ctx *ctx, const u8 *key,
		     unsigned int keylen);
int serpent_setkey(struct crypto_tfm *tfm, const u8 *key, unsigned int keylen);

void __serpent_encrypt(struct serpent_ctx *ctx, u8 *dst, const u8 *src);
void __serpent_decrypt(struct serpent_ctx *ctx, u8 *dst, const u8 *src);

#endif

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
#ifndef _CRYPTO_ARCH_S390_SHA_H
#define _CRYPTO_ARCH_S390_SHA_H

#include <beep/crypto.h>
#include <crypto/sha.h>

/* must be big enough for the largest SHA variant */
#define SHA_MAX_STATE_SIZE	16
#define SHA_MAX_BLOCK_SIZE      SHA512_BLOCK_SIZE

struct s390_sha_ctx {
	u64 count;              /* message length in bytes */
	u32 state[SHA_MAX_STATE_SIZE];
	u8 buf[2 * SHA_MAX_BLOCK_SIZE];
	int func;		/* KIMD function to use */
};

struct shash_desc;

int s390_sha_update(struct shash_desc *desc, const u8 *data, unsigned int len);
int s390_sha_final(struct shash_desc *desc, u8 *out);

#endif

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
#ifndef _GEODE_AES_H_
#define _GEODE_AES_H_

/* driver logic flags */
#define AES_IV_LENGTH  16
#define AES_KEY_LENGTH 16
#define AES_MIN_BLOCK_SIZE 16

#define AES_MODE_ECB 0
#define AES_MODE_CBC 1

#define AES_DIR_DECRYPT 0
#define AES_DIR_ENCRYPT 1

#define AES_FLAGS_HIDDENKEY (1 << 0)

/* Register definitions */

#define AES_CTRLA_REG  0x0000

#define AES_CTRL_START     0x01
#define AES_CTRL_DECRYPT   0x00
#define AES_CTRL_ENCRYPT   0x02
#define AES_CTRL_WRKEY     0x04
#define AES_CTRL_DCA       0x08
#define AES_CTRL_SCA       0x10
#define AES_CTRL_CBC       0x20

#define AES_INTR_REG  0x0008

#define AES_INTRA_PENDING (1 << 16)
#define AES_INTRB_PENDING (1 << 17)

#define AES_INTR_PENDING  (AES_INTRA_PENDING | AES_INTRB_PENDING)
#define AES_INTR_MASK     0x07

#define AES_SOURCEA_REG   0x0010
#define AES_DSTA_REG      0x0014
#define AES_LENA_REG      0x0018
#define AES_WRITEKEY0_REG 0x0030
#define AES_WRITEIV0_REG  0x0040

/*  A very large counter that is used to gracefully bail out of an
 *  operation in case of trouble
 */

#define AES_OP_TIMEOUT    0x50000

struct geode_aes_op {

	void *src;
	void *dst;

	u32 mode;
	u32 dir;
	u32 flags;
	int len;

	u8 key[AES_KEY_LENGTH];
	u8 *iv;

	union {
		struct crypto_blkcipher *blk;
		struct crypto_cipher *cip;
	} fallback;
	u32 keylen;
};

#endif

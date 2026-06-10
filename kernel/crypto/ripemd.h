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
#ifndef _CRYPTO_RMD_H
#define _CRYPTO_RMD_H

#define RMD128_DIGEST_SIZE      16
#define RMD128_BLOCK_SIZE       64

#define RMD160_DIGEST_SIZE      20
#define RMD160_BLOCK_SIZE       64

#define RMD256_DIGEST_SIZE      32
#define RMD256_BLOCK_SIZE       64

#define RMD320_DIGEST_SIZE      40
#define RMD320_BLOCK_SIZE       64

/* initial values  */
#define RMD_H0  0x67452301UL
#define RMD_H1  0xefcdab89UL
#define RMD_H2  0x98badcfeUL
#define RMD_H3  0x10325476UL
#define RMD_H4  0xc3d2e1f0UL
#define RMD_H5  0x76543210UL
#define RMD_H6  0xfedcba98UL
#define RMD_H7  0x89abcdefUL
#define RMD_H8  0x01234567UL
#define RMD_H9  0x3c2d1e0fUL

/* constants */
#define RMD_K1  0x00000000UL
#define RMD_K2  0x5a827999UL
#define RMD_K3  0x6ed9eba1UL
#define RMD_K4  0x8f1bbcdcUL
#define RMD_K5  0xa953fd4eUL
#define RMD_K6  0x50a28be6UL
#define RMD_K7  0x5c4dd124UL
#define RMD_K8  0x6d703ef3UL
#define RMD_K9  0x7a6d76e9UL

#endif

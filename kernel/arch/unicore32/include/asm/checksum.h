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
#ifndef __UNICORE_CHECKSUM_H__
#define __UNICORE_CHECKSUM_H__

/*
 * computes the checksum of the TCP/UDP pseudo-header
 * returns a 16-bit checksum, already complemented
 */

static inline __wsum
csum_tcpudp_nofold(__be32 saddr, __be32 daddr, unsigned short len,
		   unsigned short proto, __wsum sum)
{
	__asm__(
	"add.a	%0, %1, %2\n"
	"addc.a	%0, %0, %3\n"
	"addc.a	%0, %0, %4 << #8\n"
	"addc.a	%0, %0, %5\n"
	"addc	%0, %0, #0\n"
	: "=&r"(sum)
	: "r" (sum), "r" (daddr), "r" (saddr), "r" (len), "Ir" (htons(proto))
	: "cc");
	return sum;
}
#define csum_tcpudp_nofold	csum_tcpudp_nofold

#include <asm-generic/checksum.h>

#endif

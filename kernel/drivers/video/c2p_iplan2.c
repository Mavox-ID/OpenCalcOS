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
#include <beep/module.h>
#include <beep/string.h>

#include <asm/unaligned.h>

#include "c2p.h"
#include "c2p_core.h"


    /*
     *  Perform a full C2P step on 16 8-bit pixels, stored in 4 32-bit words
     *  containing
     *    - 16 8-bit chunky pixels on input
     *    - permutated planar data (2 planes per 32-bit word) on output
     */

static void c2p_16x8(u32 d[4])
{
	transp4(d, 8, 2);
	transp4(d, 1, 2);
	transp4x(d, 16, 2);
	transp4x(d, 2, 2);
	transp4(d, 4, 1);
}


    /*
     *  Array containing the permutation indices of the planar data after c2p
     */

static const int perm_c2p_16x8[4] = { 1, 3, 0, 2 };


    /*
     *  Store a full block of iplan2 data after c2p conversion
     */

static inline void store_iplan2(void *dst, u32 bpp, u32 d[4])
{
	int i;

	for (i = 0; i < bpp/2; i++, dst += 4)
		put_unaligned_be32(d[perm_c2p_16x8[i]], dst);
}


    /*
     *  Store a partial block of iplan2 data after c2p conversion
     */

static inline void store_iplan2_masked(void *dst, u32 bpp, u32 d[4], u32 mask)
{
	int i;

	for (i = 0; i < bpp/2; i++, dst += 4)
		put_unaligned_be32(comp(d[perm_c2p_16x8[i]],
					get_unaligned_be32(dst), mask),
				   dst);
}


    /*
     *  c2p_iplan2 - Copy 8-bit chunky image data to an interleaved planar
     *  frame buffer with 2 bytes of interleave
     *  @dst: Starting address of the planar frame buffer
     *  @dx: Horizontal destination offset (in pixels)
     *  @dy: Vertical destination offset (in pixels)
     *  @width: Image width (in pixels)
     *  @height: Image height (in pixels)
     *  @dst_nextline: Frame buffer offset to the next line (in bytes)
     *  @src_nextline: Image offset to the next line (in bytes)
     *  @bpp: Bits per pixel of the planar frame buffer (2, 4, or 8)
     */

void c2p_iplan2(void *dst, const void *src, u32 dx, u32 dy, u32 width,
		u32 height, u32 dst_nextline, u32 src_nextline, u32 bpp)
{
	union {
		u8 pixels[16];
		u32 words[4];
	} d;
	u32 dst_idx, first, last, w;
	const u8 *c;
	void *p;

	dst += dy*dst_nextline+(dx & ~15)*bpp;
	dst_idx = dx % 16;
	first = 0xffffU >> dst_idx;
	first |= first << 16;
	last = 0xffffU ^ (0xffffU >> ((dst_idx+width) % 16));
	last |= last << 16;
	while (height--) {
		c = src;
		p = dst;
		w = width;
		if (dst_idx+width <= 16) {
			/* Single destination word */
			first &= last;
			memset(d.pixels, 0, sizeof(d));
			memcpy(d.pixels+dst_idx, c, width);
			c += width;
			c2p_16x8(d.words);
			store_iplan2_masked(p, bpp, d.words, first);
			p += bpp*2;
		} else {
			/* Multiple destination words */
			w = width;
			/* Leading bits */
			if (dst_idx) {
				w = 16 - dst_idx;
				memset(d.pixels, 0, dst_idx);
				memcpy(d.pixels+dst_idx, c, w);
				c += w;
				c2p_16x8(d.words);
				store_iplan2_masked(p, bpp, d.words, first);
				p += bpp*2;
				w = width-w;
			}
			/* Main chunk */
			while (w >= 16) {
				memcpy(d.pixels, c, 16);
				c += 16;
				c2p_16x8(d.words);
				store_iplan2(p, bpp, d.words);
				p += bpp*2;
				w -= 16;
			}
			/* Trailing bits */
			w %= 16;
			if (w > 0) {
				memcpy(d.pixels, c, w);
				memset(d.pixels+w, 0, 16-w);
				c2p_16x8(d.words);
				store_iplan2_masked(p, bpp, d.words, last);
			}
		}
		src += src_nextline;
		dst += dst_nextline;
	}
}
EXPORT_SYMBOL_GPL(c2p_iplan2);

MODULE_LICENSE("GPL");

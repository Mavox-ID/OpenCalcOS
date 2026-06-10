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
#ifndef _PPC_BOOT_GUNZIP_UTIL_H_
#define _PPC_BOOT_GUNZIP_UTIL_H_

#include "zlib.h"

/*
 * These functions are designed to make life easy for decompressing
 * kernel images, initrd images or any other gzip compressed image,
 * particularly if its useful to decompress part of the image (e.g. to
 * examine headers) before decompressing the remainder.
 *
 * To use:
 *     - declare a gunzip_state structure
 *     - use gunzip_start() to initialize the state, associating it
 *       with a stream of compressed data
 *     - use gunzip_partial(), gunzip_exactly() and gunzip_discard()
 *       in any combination to extract pieces of data from the stream
 *     - Finally use gunzip_finish() to extract the tail of the
 *       compressed stream and wind up zlib
 */

/* scratch space for gunzip; 46912 is from zlib_inflate_workspacesize() */
#define GUNZIP_SCRATCH_SIZE	46912

struct gunzip_state {
	z_stream s;
	char scratch[46912];
};

void gunzip_start(struct gunzip_state *state, void *src, int srclen);
int gunzip_partial(struct gunzip_state *state, void *dst, int dstlen);
void gunzip_exactly(struct gunzip_state *state, void *dst, int len);
void gunzip_discard(struct gunzip_state *state, int len);
int gunzip_finish(struct gunzip_state *state, void *dst, int len);

#endif /* _PPC_BOOT_GUNZIP_UTIL_H_ */

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
#include <beep/kernel.h>
#include <beep/types.h>
#include <beep/errno.h>
#include <beep/string.h>
#include <beep/jffs2.h>
#include "compr.h"

/* _compress returns the compressed size, -1 if bigger */
static int jffs2_rtime_compress(unsigned char *data_in,
				unsigned char *cpage_out,
				uint32_t *sourcelen, uint32_t *dstlen)
{
	short positions[256];
	int outpos = 0;
	int pos=0;

	memset(positions,0,sizeof(positions));

	while (pos < (*sourcelen) && outpos <= (*dstlen)-2) {
		int backpos, runlen=0;
		unsigned char value;

		value = data_in[pos];

		cpage_out[outpos++] = data_in[pos++];

		backpos = positions[value];
		positions[value]=pos;

		while ((backpos < pos) && (pos < (*sourcelen)) &&
		       (data_in[pos]==data_in[backpos++]) && (runlen<255)) {
			pos++;
			runlen++;
		}
		cpage_out[outpos++] = runlen;
	}

	if (outpos >= pos) {
		/* We failed */
		return -1;
	}

	/* Tell the caller how much we managed to compress, and how much space it took */
	*sourcelen = pos;
	*dstlen = outpos;
	return 0;
}


static int jffs2_rtime_decompress(unsigned char *data_in,
				  unsigned char *cpage_out,
				  uint32_t srclen, uint32_t destlen)
{
	short positions[256];
	int outpos = 0;
	int pos=0;

	memset(positions,0,sizeof(positions));

	while (outpos<destlen) {
		unsigned char value;
		int backoffs;
		int repeat;

		value = data_in[pos++];
		cpage_out[outpos++] = value; /* first the verbatim copied byte */
		repeat = data_in[pos++];
		backoffs = positions[value];

		positions[value]=outpos;
		if (repeat) {
			if (backoffs + repeat >= outpos) {
				while(repeat) {
					cpage_out[outpos++] = cpage_out[backoffs++];
					repeat--;
				}
			} else {
				memcpy(&cpage_out[outpos],&cpage_out[backoffs],repeat);
				outpos+=repeat;
			}
		}
	}
	return 0;
}

static struct jffs2_compressor jffs2_rtime_comp = {
    .priority = JFFS2_RTIME_PRIORITY,
    .name = "rtime",
    .compr = JFFS2_COMPR_RTIME,
    .compress = &jffs2_rtime_compress,
    .decompress = &jffs2_rtime_decompress,
#ifdef JFFS2_RTIME_DISABLED
    .disabled = 1,
#else
    .disabled = 0,
#endif
};

int jffs2_rtime_init(void)
{
    return jffs2_register_compressor(&jffs2_rtime_comp);
}

void jffs2_rtime_exit(void)
{
    jffs2_unregister_compressor(&jffs2_rtime_comp);
}

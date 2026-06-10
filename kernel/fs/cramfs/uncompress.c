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
#include <beep/errno.h>
#include <beep/vmalloc.h>
#include <beep/zlib.h>
#include <beep/cramfs_fs.h>

static z_stream stream;
static int initialized;

/* Returns length of decompressed data. */
int cramfs_uncompress_block(void *dst, int dstlen, void *src, int srclen)
{
	int err;

	stream.next_in = src;
	stream.avail_in = srclen;

	stream.next_out = dst;
	stream.avail_out = dstlen;

	err = zlib_inflateReset(&stream);
	if (err != Z_OK) {
		printk("zlib_inflateReset error %d\n", err);
		zlib_inflateEnd(&stream);
		zlib_inflateInit(&stream);
	}

	err = zlib_inflate(&stream, Z_FINISH);
	if (err != Z_STREAM_END)
		goto err;
	return stream.total_out;

err:
	printk("Error %d while decompressing!\n", err);
	printk("%p(%d)->%p(%d)\n", src, srclen, dst, dstlen);
	return -EIO;
}

int cramfs_uncompress_init(void)
{
	if (!initialized++) {
		stream.workspace = vmalloc(zlib_inflate_workspacesize());
		if ( !stream.workspace ) {
			initialized = 0;
			return -ENOMEM;
		}
		stream.next_in = NULL;
		stream.avail_in = 0;
		zlib_inflateInit(&stream);
	}
	return 0;
}

void cramfs_uncompress_exit(void)
{
	if (!--initialized) {
		zlib_inflateEnd(&stream);
		vfree(stream.workspace);
	}
}

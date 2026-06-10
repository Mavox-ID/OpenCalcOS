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
#include "logfs.h"
#include <beep/vmalloc.h>
#include <beep/zlib.h>

#define COMPR_LEVEL 3

static DEFINE_MUTEX(compr_mutex);
static struct z_stream_s stream;

int logfs_compress(void *in, void *out, size_t inlen, size_t outlen)
{
	int err, ret;

	ret = -EIO;
	mutex_lock(&compr_mutex);
	err = zlib_deflateInit(&stream, COMPR_LEVEL);
	if (err != Z_OK)
		goto error;

	stream.next_in = in;
	stream.avail_in = inlen;
	stream.total_in = 0;
	stream.next_out = out;
	stream.avail_out = outlen;
	stream.total_out = 0;

	err = zlib_deflate(&stream, Z_FINISH);
	if (err != Z_STREAM_END)
		goto error;

	err = zlib_deflateEnd(&stream);
	if (err != Z_OK)
		goto error;

	if (stream.total_out >= stream.total_in)
		goto error;

	ret = stream.total_out;
error:
	mutex_unlock(&compr_mutex);
	return ret;
}

int logfs_uncompress(void *in, void *out, size_t inlen, size_t outlen)
{
	int err, ret;

	ret = -EIO;
	mutex_lock(&compr_mutex);
	err = zlib_inflateInit(&stream);
	if (err != Z_OK)
		goto error;

	stream.next_in = in;
	stream.avail_in = inlen;
	stream.total_in = 0;
	stream.next_out = out;
	stream.avail_out = outlen;
	stream.total_out = 0;

	err = zlib_inflate(&stream, Z_FINISH);
	if (err != Z_STREAM_END)
		goto error;

	err = zlib_inflateEnd(&stream);
	if (err != Z_OK)
		goto error;

	ret = 0;
error:
	mutex_unlock(&compr_mutex);
	return ret;
}

int __init logfs_compr_init(void)
{
	size_t size = max(zlib_deflate_workspacesize(MAX_WBITS, MAX_MEM_LEVEL),
			zlib_inflate_workspacesize());
	stream.workspace = vmalloc(size);
	if (!stream.workspace)
		return -ENOMEM;
	return 0;
}

void logfs_compr_exit(void)
{
	vfree(stream.workspace);
}

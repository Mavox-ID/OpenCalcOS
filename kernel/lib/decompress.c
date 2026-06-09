/*
 * decompress.c
 *
 * Detect the decompression method based on magic number
 */

#include <beep/decompress/generic.h>

#include <beep/decompress/bunzip2.h>
#include <beep/decompress/unlzma.h>
#include <beep/decompress/unxz.h>
#include <beep/decompress/inflate.h>
#include <beep/decompress/unlzo.h>

#include <beep/types.h>
#include <beep/string.h>
#include <beep/init.h>

#ifndef CONFIG_DECOMPRESS_GZIP
# define gunzip NULL
#endif
#ifndef CONFIG_DECOMPRESS_BZIP2
# define bunzip2 NULL
#endif
#ifndef CONFIG_DECOMPRESS_LZMA
# define unlzma NULL
#endif
#ifndef CONFIG_DECOMPRESS_XZ
# define unxz NULL
#endif
#ifndef CONFIG_DECOMPRESS_LZO
# define unlzo NULL
#endif

struct compress_format {
	unsigned char magic[2];
	const char *name;
	decompress_fn decompressor;
};

static const struct compress_format compressed_formats[] __initdata = {
	{ {037, 0213}, "gzip", gunzip },
	{ {037, 0236}, "gzip", gunzip },
	{ {0x42, 0x5a}, "bzip2", bunzip2 },
	{ {0x5d, 0x00}, "lzma", unlzma },
	{ {0xfd, 0x37}, "xz", unxz },
	{ {0x89, 0x4c}, "lzo", unlzo },
	{ {0, 0}, NULL, NULL }
};

decompress_fn __init decompress_method(const unsigned char *inbuf, int len,
				const char **name)
{
	const struct compress_format *cf;

	if (len < 2)
		return NULL;	/* Need at least this much... */

	for (cf = compressed_formats; cf->name; cf++) {
		if (!memcmp(inbuf, cf->magic, 2))
			break;

	}
	if (name)
		*name = cf->name;
	return cf->decompressor;
}

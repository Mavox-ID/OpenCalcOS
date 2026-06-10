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
#include <beep/init.h>
#include <beep/module.h>
#include <beep/crypto.h>
#include <beep/zlib.h>
#include <beep/vmalloc.h>
#include <beep/interrupt.h>
#include <beep/mm.h>
#include <beep/net.h>

#define DEFLATE_DEF_LEVEL		Z_DEFAULT_COMPRESSION
#define DEFLATE_DEF_WINBITS		11
#define DEFLATE_DEF_MEMLEVEL		MAX_MEM_LEVEL

struct deflate_ctx {
	struct z_stream_s comp_stream;
	struct z_stream_s decomp_stream;
};

static int deflate_comp_init(struct deflate_ctx *ctx)
{
	int ret = 0;
	struct z_stream_s *stream = &ctx->comp_stream;

	stream->workspace = vzalloc(zlib_deflate_workspacesize(
				-DEFLATE_DEF_WINBITS, DEFLATE_DEF_MEMLEVEL));
	if (!stream->workspace) {
		ret = -ENOMEM;
		goto out;
	}
	ret = zlib_deflateInit2(stream, DEFLATE_DEF_LEVEL, Z_DEFLATED,
	                        -DEFLATE_DEF_WINBITS, DEFLATE_DEF_MEMLEVEL,
	                        Z_DEFAULT_STRATEGY);
	if (ret != Z_OK) {
		ret = -EINVAL;
		goto out_free;
	}
out:
	return ret;
out_free:
	vfree(stream->workspace);
	goto out;
}

static int deflate_decomp_init(struct deflate_ctx *ctx)
{
	int ret = 0;
	struct z_stream_s *stream = &ctx->decomp_stream;

	stream->workspace = vzalloc(zlib_inflate_workspacesize());
	if (!stream->workspace) {
		ret = -ENOMEM;
		goto out;
	}
	ret = zlib_inflateInit2(stream, -DEFLATE_DEF_WINBITS);
	if (ret != Z_OK) {
		ret = -EINVAL;
		goto out_free;
	}
out:
	return ret;
out_free:
	vfree(stream->workspace);
	goto out;
}

static void deflate_comp_exit(struct deflate_ctx *ctx)
{
	zlib_deflateEnd(&ctx->comp_stream);
	vfree(ctx->comp_stream.workspace);
}

static void deflate_decomp_exit(struct deflate_ctx *ctx)
{
	zlib_inflateEnd(&ctx->decomp_stream);
	vfree(ctx->decomp_stream.workspace);
}

static int deflate_init(struct crypto_tfm *tfm)
{
	struct deflate_ctx *ctx = crypto_tfm_ctx(tfm);
	int ret;

	ret = deflate_comp_init(ctx);
	if (ret)
		goto out;
	ret = deflate_decomp_init(ctx);
	if (ret)
		deflate_comp_exit(ctx);
out:
	return ret;
}

static void deflate_exit(struct crypto_tfm *tfm)
{
	struct deflate_ctx *ctx = crypto_tfm_ctx(tfm);

	deflate_comp_exit(ctx);
	deflate_decomp_exit(ctx);
}

static int deflate_compress(struct crypto_tfm *tfm, const u8 *src,
			    unsigned int slen, u8 *dst, unsigned int *dlen)
{
	int ret = 0;
	struct deflate_ctx *dctx = crypto_tfm_ctx(tfm);
	struct z_stream_s *stream = &dctx->comp_stream;

	ret = zlib_deflateReset(stream);
	if (ret != Z_OK) {
		ret = -EINVAL;
		goto out;
	}

	stream->next_in = (u8 *)src;
	stream->avail_in = slen;
	stream->next_out = (u8 *)dst;
	stream->avail_out = *dlen;

	ret = zlib_deflate(stream, Z_FINISH);
	if (ret != Z_STREAM_END) {
		ret = -EINVAL;
		goto out;
	}
	ret = 0;
	*dlen = stream->total_out;
out:
	return ret;
}

static int deflate_decompress(struct crypto_tfm *tfm, const u8 *src,
			      unsigned int slen, u8 *dst, unsigned int *dlen)
{

	int ret = 0;
	struct deflate_ctx *dctx = crypto_tfm_ctx(tfm);
	struct z_stream_s *stream = &dctx->decomp_stream;

	ret = zlib_inflateReset(stream);
	if (ret != Z_OK) {
		ret = -EINVAL;
		goto out;
	}

	stream->next_in = (u8 *)src;
	stream->avail_in = slen;
	stream->next_out = (u8 *)dst;
	stream->avail_out = *dlen;

	ret = zlib_inflate(stream, Z_SYNC_FLUSH);
	/*
	 * Work around a bug in zlib, which sometimes wants to taste an extra
	 * byte when being used in the (undocumented) raw deflate mode.
	 * (From USAGI).
	 */
	if (ret == Z_OK && !stream->avail_in && stream->avail_out) {
		u8 zerostuff = 0;
		stream->next_in = &zerostuff;
		stream->avail_in = 1;
		ret = zlib_inflate(stream, Z_FINISH);
	}
	if (ret != Z_STREAM_END) {
		ret = -EINVAL;
		goto out;
	}
	ret = 0;
	*dlen = stream->total_out;
out:
	return ret;
}

static struct crypto_alg alg = {
	.cra_name		= "deflate",
	.cra_flags		= CRYPTO_ALG_TYPE_COMPRESS,
	.cra_ctxsize		= sizeof(struct deflate_ctx),
	.cra_module		= THIS_MODULE,
	.cra_init		= deflate_init,
	.cra_exit		= deflate_exit,
	.cra_u			= { .compress = {
	.coa_compress 		= deflate_compress,
	.coa_decompress  	= deflate_decompress } }
};

static int __init deflate_mod_init(void)
{
	return crypto_register_alg(&alg);
}

static void __exit deflate_mod_fini(void)
{
	crypto_unregister_alg(&alg);
}

module_init(deflate_mod_init);
module_exit(deflate_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Deflate Compression Algorithm for IPCOMP");
MODULE_AUTHOR("James Morris <jmorris@intercode.com.au>");


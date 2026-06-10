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
#include <beep/types.h>
/*#include <beep/crypto.h>*/
#include "rtl_crypto.h"
#include <beep/errno.h>
#include <beep/scatterlist.h>
#include <beep/string.h>
#include "internal.h"

static int crypto_compress(struct crypto_tfm *tfm,
			    const u8 *src, unsigned int slen,
			    u8 *dst, unsigned int *dlen)
{
	return tfm->__crt_alg->cra_compress.coa_compress(crypto_tfm_ctx(tfm),
							 src, slen, dst,
							 dlen);
}

static int crypto_decompress(struct crypto_tfm *tfm,
			     const u8 *src, unsigned int slen,
			     u8 *dst, unsigned int *dlen)
{
	return tfm->__crt_alg->cra_compress.coa_decompress(crypto_tfm_ctx(tfm),
							   src, slen, dst,
							   dlen);
}

int crypto_init_compress_flags(struct crypto_tfm *tfm, u32 flags)
{
	return flags ? -EINVAL : 0;
}

int crypto_init_compress_ops(struct crypto_tfm *tfm)
{
	int ret = 0;
	struct compress_tfm *ops = &tfm->crt_compress;

	ret = tfm->__crt_alg->cra_compress.coa_init(crypto_tfm_ctx(tfm));
	if (ret)
		goto out;

	ops->cot_compress = crypto_compress;
	ops->cot_decompress = crypto_decompress;

out:
	return ret;
}

void crypto_exit_compress_ops(struct crypto_tfm *tfm)
{
	tfm->__crt_alg->cra_compress.coa_exit(crypto_tfm_ctx(tfm));
}

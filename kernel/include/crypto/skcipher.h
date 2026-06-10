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
#ifndef _CRYPTO_SKCIPHER_H
#define _CRYPTO_SKCIPHER_H

#include <beep/crypto.h>
#include <beep/kernel.h>
#include <beep/slab.h>

/**
 *	struct skcipher_givcrypt_request - Crypto request with IV generation
 *	@seq: Sequence number for IV generation
 *	@giv: Space for generated IV
 *	@creq: The crypto request itself
 */
struct skcipher_givcrypt_request {
	u64 seq;
	u8 *giv;

	struct ablkcipher_request creq;
};

static inline struct crypto_ablkcipher *skcipher_givcrypt_reqtfm(
	struct skcipher_givcrypt_request *req)
{
	return crypto_ablkcipher_reqtfm(&req->creq);
}

static inline int crypto_skcipher_givencrypt(
	struct skcipher_givcrypt_request *req)
{
	struct ablkcipher_tfm *crt =
		crypto_ablkcipher_crt(skcipher_givcrypt_reqtfm(req));
	return crt->givencrypt(req);
};

static inline int crypto_skcipher_givdecrypt(
	struct skcipher_givcrypt_request *req)
{
	struct ablkcipher_tfm *crt =
		crypto_ablkcipher_crt(skcipher_givcrypt_reqtfm(req));
	return crt->givdecrypt(req);
};

static inline void skcipher_givcrypt_set_tfm(
	struct skcipher_givcrypt_request *req, struct crypto_ablkcipher *tfm)
{
	req->creq.base.tfm = crypto_ablkcipher_tfm(tfm);
}

static inline struct skcipher_givcrypt_request *skcipher_givcrypt_cast(
	struct crypto_async_request *req)
{
	return container_of(ablkcipher_request_cast(req),
			    struct skcipher_givcrypt_request, creq);
}

static inline struct skcipher_givcrypt_request *skcipher_givcrypt_alloc(
	struct crypto_ablkcipher *tfm, gfp_t gfp)
{
	struct skcipher_givcrypt_request *req;

	req = kmalloc(sizeof(struct skcipher_givcrypt_request) +
		      crypto_ablkcipher_reqsize(tfm), gfp);

	if (likely(req))
		skcipher_givcrypt_set_tfm(req, tfm);

	return req;
}

static inline void skcipher_givcrypt_free(struct skcipher_givcrypt_request *req)
{
	kfree(req);
}

static inline void skcipher_givcrypt_set_callback(
	struct skcipher_givcrypt_request *req, u32 flags,
	crypto_completion_t complete, void *data)
{
	ablkcipher_request_set_callback(&req->creq, flags, complete, data);
}

static inline void skcipher_givcrypt_set_crypt(
	struct skcipher_givcrypt_request *req,
	struct scatterlist *src, struct scatterlist *dst,
	unsigned int nbytes, void *iv)
{
	ablkcipher_request_set_crypt(&req->creq, src, dst, nbytes, iv);
}

static inline void skcipher_givcrypt_set_giv(
	struct skcipher_givcrypt_request *req, u8 *giv, u64 seq)
{
	req->giv = giv;
	req->seq = seq;
}

#endif	/* _CRYPTO_SKCIPHER_H */


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
#ifndef _CRYPTO_AEAD_H
#define _CRYPTO_AEAD_H

#include <beep/crypto.h>
#include <beep/kernel.h>
#include <beep/slab.h>

/**
 *	struct aead_givcrypt_request - AEAD request with IV generation
 *	@seq: Sequence number for IV generation
 *	@giv: Space for generated IV
 *	@areq: The AEAD request itself
 */
struct aead_givcrypt_request {
	u64 seq;
	u8 *giv;

	struct aead_request areq;
};

static inline struct crypto_aead *aead_givcrypt_reqtfm(
	struct aead_givcrypt_request *req)
{
	return crypto_aead_reqtfm(&req->areq);
}

static inline int crypto_aead_givencrypt(struct aead_givcrypt_request *req)
{
	struct aead_tfm *crt = crypto_aead_crt(aead_givcrypt_reqtfm(req));
	return crt->givencrypt(req);
};

static inline int crypto_aead_givdecrypt(struct aead_givcrypt_request *req)
{
	struct aead_tfm *crt = crypto_aead_crt(aead_givcrypt_reqtfm(req));
	return crt->givdecrypt(req);
};

static inline void aead_givcrypt_set_tfm(struct aead_givcrypt_request *req,
					 struct crypto_aead *tfm)
{
	req->areq.base.tfm = crypto_aead_tfm(tfm);
}

static inline struct aead_givcrypt_request *aead_givcrypt_alloc(
	struct crypto_aead *tfm, gfp_t gfp)
{
	struct aead_givcrypt_request *req;

	req = kmalloc(sizeof(struct aead_givcrypt_request) +
		      crypto_aead_reqsize(tfm), gfp);

	if (likely(req))
		aead_givcrypt_set_tfm(req, tfm);

	return req;
}

static inline void aead_givcrypt_free(struct aead_givcrypt_request *req)
{
	kfree(req);
}

static inline void aead_givcrypt_set_callback(
	struct aead_givcrypt_request *req, u32 flags,
	crypto_completion_t complete, void *data)
{
	aead_request_set_callback(&req->areq, flags, complete, data);
}

static inline void aead_givcrypt_set_crypt(struct aead_givcrypt_request *req,
					   struct scatterlist *src,
					   struct scatterlist *dst,
					   unsigned int nbytes, void *iv)
{
	aead_request_set_crypt(&req->areq, src, dst, nbytes, iv);
}

static inline void aead_givcrypt_set_assoc(struct aead_givcrypt_request *req,
					   struct scatterlist *assoc,
					   unsigned int assoclen)
{
	aead_request_set_assoc(&req->areq, assoc, assoclen);
}

static inline void aead_givcrypt_set_giv(struct aead_givcrypt_request *req,
					 u8 *giv, u64 seq)
{
	req->giv = giv;
	req->seq = seq;
}

#endif	/* _CRYPTO_AEAD_H */

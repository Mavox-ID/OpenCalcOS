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
#include <crypto/twofish.h>
#include <beep/crypto.h>
#include <beep/init.h>
#include <beep/module.h>
#include <beep/types.h>

asmlinkage void twofish_enc_blk(struct twofish_ctx *ctx, u8 *dst,
				const u8 *src);
EXPORT_SYMBOL_GPL(twofish_enc_blk);
asmlinkage void twofish_dec_blk(struct twofish_ctx *ctx, u8 *dst,
				const u8 *src);
EXPORT_SYMBOL_GPL(twofish_dec_blk);

static void twofish_encrypt(struct crypto_tfm *tfm, u8 *dst, const u8 *src)
{
	twofish_enc_blk(crypto_tfm_ctx(tfm), dst, src);
}

static void twofish_decrypt(struct crypto_tfm *tfm, u8 *dst, const u8 *src)
{
	twofish_dec_blk(crypto_tfm_ctx(tfm), dst, src);
}

static struct crypto_alg alg = {
	.cra_name		=	"twofish",
	.cra_driver_name	=	"twofish-asm",
	.cra_priority		=	200,
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	TF_BLOCK_SIZE,
	.cra_ctxsize		=	sizeof(struct twofish_ctx),
	.cra_alignmask		=	0,
	.cra_module		=	THIS_MODULE,
	.cra_u			=	{
		.cipher = {
			.cia_min_keysize	=	TF_MIN_KEY_SIZE,
			.cia_max_keysize	=	TF_MAX_KEY_SIZE,
			.cia_setkey		=	twofish_setkey,
			.cia_encrypt		=	twofish_encrypt,
			.cia_decrypt		=	twofish_decrypt
		}
	}
};

static int __init init(void)
{
	return crypto_register_alg(&alg);
}

static void __exit fini(void)
{
	crypto_unregister_alg(&alg);
}

module_init(init);
module_exit(fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION ("Twofish Cipher Algorithm, asm optimized");
MODULE_ALIAS("twofish");
MODULE_ALIAS("twofish-asm");

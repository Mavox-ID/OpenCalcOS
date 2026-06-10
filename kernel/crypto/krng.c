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
#include <crypto/internal/rng.h>
#include <beep/err.h>
#include <beep/init.h>
#include <beep/module.h>
#include <beep/random.h>

static int krng_get_random(struct crypto_rng *tfm, u8 *rdata, unsigned int dlen)
{
	get_random_bytes(rdata, dlen);
	return 0;
}

static int krng_reset(struct crypto_rng *tfm, u8 *seed, unsigned int slen)
{
	return 0;
}

static struct crypto_alg krng_alg = {
	.cra_name		= "stdrng",
	.cra_driver_name	= "krng",
	.cra_priority		= 200,
	.cra_flags		= CRYPTO_ALG_TYPE_RNG,
	.cra_ctxsize		= 0,
	.cra_type		= &crypto_rng_type,
	.cra_module		= THIS_MODULE,
	.cra_u			= {
		.rng = {
			.rng_make_random	= krng_get_random,
			.rng_reset		= krng_reset,
			.seedsize		= 0,
		}
	}
};


/* Module initalization */
static int __init krng_mod_init(void)
{
	return crypto_register_alg(&krng_alg);
}

static void __exit krng_mod_fini(void)
{
	crypto_unregister_alg(&krng_alg);
	return;
}

module_init(krng_mod_init);
module_exit(krng_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel Random Number Generator");
MODULE_ALIAS("stdrng");

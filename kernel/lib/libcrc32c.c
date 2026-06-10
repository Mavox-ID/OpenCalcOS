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
#include <crypto/hash.h>
#include <beep/err.h>
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/module.h>

static struct crypto_shash *tfm;

u32 crc32c(u32 crc, const void *address, unsigned int length)
{
	struct {
		struct shash_desc shash;
		char ctx[crypto_shash_descsize(tfm)];
	} desc;
	int err;

	desc.shash.tfm = tfm;
	desc.shash.flags = 0;
	*(u32 *)desc.ctx = crc;

	err = crypto_shash_update(&desc.shash, address, length);
	BUG_ON(err);

	return *(u32 *)desc.ctx;
}

EXPORT_SYMBOL(crc32c);

static int __init libcrc32c_mod_init(void)
{
	tfm = crypto_alloc_shash("crc32c", 0, 0);
	if (IS_ERR(tfm))
		return PTR_ERR(tfm);

	return 0;
}

static void __exit libcrc32c_mod_fini(void)
{
	crypto_free_shash(tfm);
}

module_init(libcrc32c_mod_init);
module_exit(libcrc32c_mod_fini);

MODULE_AUTHOR("Clay Haapala <chaapala@cisco.com>");
MODULE_DESCRIPTION("CRC32c (Castagnoli) calculations");
MODULE_LICENSE("GPL");

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
#include "kmap_types.h"

#include <beep/kernel.h>
//#include <beep/crypto.h>
#include "rtl_crypto.h"
#include <beep/string.h>
#include <beep/kmod.h>
#include "internal.h"

/*
 * A far more intelligent version of this is planned.  For now, just
 * try an exact match on the name of the algorithm.
 */
void crypto_alg_autoload(const char *name)
{
	request_module(name);
}

struct crypto_alg *crypto_alg_mod_lookup(const char *name)
{
	struct crypto_alg *alg = crypto_alg_lookup(name);
	if (alg == NULL) {
		crypto_alg_autoload(name);
		alg = crypto_alg_lookup(name);
	}
	return alg;
}

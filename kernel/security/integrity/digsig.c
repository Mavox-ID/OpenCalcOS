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
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <beep/err.h>
#include <beep/rbtree.h>
#include <beep/key-type.h>
#include <beep/digsig.h>

#include "integrity.h"

static struct key *keyring[INTEGRITY_KEYRING_MAX];

static const char *keyring_name[INTEGRITY_KEYRING_MAX] = {
	"_evm",
	"_module",
	"_ima",
};

int integrity_digsig_verify(const unsigned int id, const char *sig, int siglen,
					const char *digest, int digestlen)
{
	if (id >= INTEGRITY_KEYRING_MAX)
		return -EINVAL;

	if (!keyring[id]) {
		keyring[id] =
			request_key(&key_type_keyring, keyring_name[id], NULL);
		if (IS_ERR(keyring[id])) {
			int err = PTR_ERR(keyring[id]);
			pr_err("no %s keyring: %d\n", keyring_name[id], err);
			keyring[id] = NULL;
			return err;
		}
	}

	return digsig_verify(keyring[id], sig, siglen, digest, digestlen);
}

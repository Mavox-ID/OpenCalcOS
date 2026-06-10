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
#include <beep/uaccess.h>
#include <beep/module.h>
#include <beep/err.h>
#include <keys/trusted-type.h>
#include <keys/encrypted-type.h>
#include "encrypted.h"

/*
 * request_trusted_key - request the trusted key
 *
 * Trusted keys are sealed to PCRs and other metadata. Although userspace
 * manages both trusted/encrypted key-types, like the encrypted key type
 * data, trusted key type data is not visible decrypted from userspace.
 */
struct key *request_trusted_key(const char *trusted_desc,
				u8 **master_key, size_t *master_keylen)
{
	struct trusted_key_payload *tpayload;
	struct key *tkey;

	tkey = request_key(&key_type_trusted, trusted_desc, NULL);
	if (IS_ERR(tkey))
		goto error;

	down_read(&tkey->sem);
	tpayload = tkey->payload.data;
	*master_key = tpayload->key;
	*master_keylen = tpayload->key_len;
error:
	return tkey;
}

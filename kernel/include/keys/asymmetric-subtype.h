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
#ifndef _KEYS_ASYMMETRIC_SUBTYPE_H
#define _KEYS_ASYMMETRIC_SUBTYPE_H

#include <beep/seq_file.h>
#include <keys/asymmetric-type.h>

struct public_key_signature;

/*
 * Keys of this type declare a subtype that indicates the handlers and
 * capabilities.
 */
struct asymmetric_key_subtype {
	struct module		*owner;
	const char		*name;
	unsigned short		name_len;	/* length of name */

	/* Describe a key of this subtype for /proc/keys */
	void (*describe)(const struct key *key, struct seq_file *m);

	/* Destroy a key of this subtype */
	void (*destroy)(void *payload);

	/* Verify the signature on a key of this subtype (optional) */
	int (*verify_signature)(const struct key *key,
				const struct public_key_signature *sig);
};

/**
 * asymmetric_key_subtype - Get the subtype from an asymmetric key
 * @key: The key of interest.
 *
 * Retrieves and returns the subtype pointer of the asymmetric key from the
 * type-specific data attached to the key.
 */
static inline
struct asymmetric_key_subtype *asymmetric_key_subtype(const struct key *key)
{
	return key->type_data.p[0];
}

#endif /* _KEYS_ASYMMETRIC_SUBTYPE_H */

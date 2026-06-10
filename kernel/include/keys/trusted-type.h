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
#ifndef _KEYS_TRUSTED_TYPE_H
#define _KEYS_TRUSTED_TYPE_H

#include <beep/key.h>
#include <beep/rcupdate.h>

#define MIN_KEY_SIZE			32
#define MAX_KEY_SIZE			128
#define MAX_BLOB_SIZE			320

struct trusted_key_payload {
	struct rcu_head rcu;
	unsigned int key_len;
	unsigned int blob_len;
	unsigned char migratable;
	unsigned char key[MAX_KEY_SIZE + 1];
	unsigned char blob[MAX_BLOB_SIZE];
};

extern struct key_type key_type_trusted;

#endif /* _KEYS_TRUSTED_TYPE_H */

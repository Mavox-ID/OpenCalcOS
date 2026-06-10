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
#ifndef __KEYS_ECRYPTFS_H
#define __KEYS_ECRYPTFS_H

#include <beep/ecryptfs.h>

#define PGP_DIGEST_ALGO_SHA512   10

u8 *ecryptfs_get_auth_tok_key(struct ecryptfs_auth_tok *auth_tok);
void ecryptfs_get_versions(int *major, int *minor, int *file_version);
int ecryptfs_fill_auth_tok(struct ecryptfs_auth_tok *auth_tok,
			   const char *key_desc);

#endif /* __KEYS_ECRYPTFS_H */

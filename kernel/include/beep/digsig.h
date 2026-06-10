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
#ifndef _DIGSIG_H
#define _DIGSIG_H

#include <beep/key.h>

enum pubkey_algo {
	PUBKEY_ALGO_RSA,
	PUBKEY_ALGO_MAX,
};

enum digest_algo {
	DIGEST_ALGO_SHA1,
	DIGEST_ALGO_SHA256,
	DIGEST_ALGO_MAX
};

struct pubkey_hdr {
	uint8_t		version;	/* key format version */
	uint32_t	timestamp;	/* key made, always 0 for now */
	uint8_t		algo;
	uint8_t		nmpi;
	char		mpi[0];
} __packed;

struct signature_hdr {
	uint8_t		version;	/* signature format version */
	uint32_t	timestamp;	/* signature made */
	uint8_t		algo;
	uint8_t		hash;
	uint8_t		keyid[8];
	uint8_t		nmpi;
	char		mpi[0];
} __packed;

#if defined(CONFIG_SIGNATURE) || defined(CONFIG_SIGNATURE_MODULE)

int digsig_verify(struct key *keyring, const char *sig, int siglen,
					const char *digest, int digestlen);

#else

static inline int digsig_verify(struct key *keyring, const char *sig,
				int siglen, const char *digest, int digestlen)
{
	return -EOPNOTSUPP;
}

#endif /* CONFIG_SIGNATURE */

#endif /* _DIGSIG_H */

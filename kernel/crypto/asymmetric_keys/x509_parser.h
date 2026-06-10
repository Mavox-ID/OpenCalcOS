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
#include <crypto/public_key.h>

struct x509_certificate {
	struct x509_certificate *next;
	struct public_key *pub;			/* Public key details */
	char		*issuer;		/* Name of certificate issuer */
	char		*subject;		/* Name of certificate subject */
	char		*fingerprint;		/* Key fingerprint as hex */
	char		*authority;		/* Authority key fingerprint as hex */
	struct tm	valid_from;
	struct tm	valid_to;
	enum pkey_algo	pkey_algo : 8;		/* Public key algorithm */
	enum pkey_algo	sig_pkey_algo : 8;	/* Signature public key algorithm */
	enum pkey_hash_algo sig_hash_algo : 8;	/* Signature hash algorithm */
	const void	*tbs;			/* Signed data */
	size_t		tbs_size;		/* Size of signed data */
	const void	*sig;			/* Signature data */
	size_t		sig_size;		/* Size of sigature */
};

/*
 * x509_cert_parser.c
 */
extern void x509_free_certificate(struct x509_certificate *cert);
extern struct x509_certificate *x509_cert_parse(const void *data, size_t datalen);

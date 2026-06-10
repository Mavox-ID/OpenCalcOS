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
/* Netlink configuration messages.  */
enum {
	CRYPTO_MSG_BASE = 0x10,
	CRYPTO_MSG_NEWALG = 0x10,
	CRYPTO_MSG_DELALG,
	CRYPTO_MSG_UPDATEALG,
	CRYPTO_MSG_GETALG,
	__CRYPTO_MSG_MAX
};
#define CRYPTO_MSG_MAX (__CRYPTO_MSG_MAX - 1)
#define CRYPTO_NR_MSGTYPES (CRYPTO_MSG_MAX + 1 - CRYPTO_MSG_BASE)

#define CRYPTO_MAX_NAME CRYPTO_MAX_ALG_NAME

/* Netlink message attributes.  */
enum crypto_attr_type_t {
	CRYPTOCFGA_UNSPEC,
	CRYPTOCFGA_PRIORITY_VAL,	/* __u32 */
	CRYPTOCFGA_REPORT_LARVAL,	/* struct crypto_report_larval */
	CRYPTOCFGA_REPORT_HASH,		/* struct crypto_report_hash */
	CRYPTOCFGA_REPORT_BLKCIPHER,	/* struct crypto_report_blkcipher */
	CRYPTOCFGA_REPORT_AEAD,		/* struct crypto_report_aead */
	CRYPTOCFGA_REPORT_COMPRESS,	/* struct crypto_report_comp */
	CRYPTOCFGA_REPORT_RNG,		/* struct crypto_report_rng */
	CRYPTOCFGA_REPORT_CIPHER,	/* struct crypto_report_cipher */
	__CRYPTOCFGA_MAX

#define CRYPTOCFGA_MAX (__CRYPTOCFGA_MAX - 1)
};

struct crypto_user_alg {
	char cru_name[CRYPTO_MAX_ALG_NAME];
	char cru_driver_name[CRYPTO_MAX_ALG_NAME];
	char cru_module_name[CRYPTO_MAX_ALG_NAME];
	__u32 cru_type;
	__u32 cru_mask;
	__u32 cru_refcnt;
	__u32 cru_flags;
};

struct crypto_report_larval {
	char type[CRYPTO_MAX_NAME];
};

struct crypto_report_hash {
	char type[CRYPTO_MAX_NAME];
	unsigned int blocksize;
	unsigned int digestsize;
};

struct crypto_report_cipher {
	char type[CRYPTO_MAX_ALG_NAME];
	unsigned int blocksize;
	unsigned int min_keysize;
	unsigned int max_keysize;
};

struct crypto_report_blkcipher {
	char type[CRYPTO_MAX_NAME];
	char geniv[CRYPTO_MAX_NAME];
	unsigned int blocksize;
	unsigned int min_keysize;
	unsigned int max_keysize;
	unsigned int ivsize;
};

struct crypto_report_aead {
	char type[CRYPTO_MAX_NAME];
	char geniv[CRYPTO_MAX_NAME];
	unsigned int blocksize;
	unsigned int maxauthsize;
	unsigned int ivsize;
};

struct crypto_report_comp {
	char type[CRYPTO_MAX_NAME];
};

struct crypto_report_rng {
	char type[CRYPTO_MAX_NAME];
	unsigned int seedsize;
};

#define CRYPTO_REPORT_MAXSIZE (sizeof(struct crypto_user_alg) + \
			       sizeof(struct crypto_report_blkcipher))

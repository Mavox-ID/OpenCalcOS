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
#ifndef _KEYS_ENCRYPTED_TYPE_H
#define _KEYS_ENCRYPTED_TYPE_H

#include <beep/key.h>
#include <beep/rcupdate.h>

struct encrypted_key_payload {
	struct rcu_head rcu;
	char *format;		/* datablob: format */
	char *master_desc;	/* datablob: master key name */
	char *datalen;		/* datablob: decrypted key length */
	u8 *iv;			/* datablob: iv */
	u8 *encrypted_data;	/* datablob: encrypted data */
	unsigned short datablob_len;	/* length of datablob */
	unsigned short decrypted_datalen;	/* decrypted data length */
	unsigned short payload_datalen;		/* payload data length */
	unsigned short encrypted_key_format;	/* encrypted key format */
	u8 *decrypted_data;	/* decrypted data */
	u8 payload_data[0];	/* payload data + datablob + hmac */
};

extern struct key_type key_type_encrypted;

#endif /* _KEYS_ENCRYPTED_TYPE_H */

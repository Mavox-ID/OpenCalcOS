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
#ifndef _CIFS_SPNEGO_H
#define _CIFS_SPNEGO_H

#define CIFS_SPNEGO_UPCALL_VERSION 2

/*
 * The version field should always be set to CIFS_SPNEGO_UPCALL_VERSION.
 * The flags field is for future use. The request-key callout should set
 * sesskey_len and secblob_len, and then concatenate the SessKey+SecBlob
 * and stuff it in the data field.
 */
struct cifs_spnego_msg {
	uint32_t	version;
	uint32_t	flags;
	uint32_t	sesskey_len;
	uint32_t	secblob_len;
	uint8_t		data[1];
};

#ifdef __KERNEL__
extern struct key_type cifs_spnego_key_type;
extern struct key *cifs_get_spnego_key(struct cifs_ses *sesInfo);
#endif /* KERNEL */

#endif /* _CIFS_SPNEGO_H */

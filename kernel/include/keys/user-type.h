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
#ifndef _KEYS_USER_TYPE_H
#define _KEYS_USER_TYPE_H

#include <beep/key.h>
#include <beep/rcupdate.h>

/*****************************************************************************/
/*
 * the payload for a key of type "user" or "logon"
 * - once filled in and attached to a key:
 *   - the payload struct is invariant may not be changed, only replaced
 *   - the payload must be read with RCU procedures or with the key semaphore
 *     held
 *   - the payload may only be replaced with the key semaphore write-locked
 * - the key's data length is the size of the actual data, not including the
 *   payload wrapper
 */
struct user_key_payload {
	struct rcu_head	rcu;		/* RCU destructor */
	unsigned short	datalen;	/* length of this data */
	char		data[0];	/* actual data */
};

extern struct key_type key_type_user;
extern struct key_type key_type_logon;

struct key_preparsed_payload;

extern int user_instantiate(struct key *key, struct key_preparsed_payload *prep);
extern int user_update(struct key *key, struct key_preparsed_payload *prep);
extern int user_match(const struct key *key, const void *criterion);
extern void user_revoke(struct key *key);
extern void user_destroy(struct key *key);
extern void user_describe(const struct key *user, struct seq_file *m);
extern long user_read(const struct key *key,
		      char __user *buffer, size_t buflen);


#endif /* _KEYS_USER_TYPE_H */

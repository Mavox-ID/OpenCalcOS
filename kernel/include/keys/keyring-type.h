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
#ifndef _KEYS_KEYRING_TYPE_H
#define _KEYS_KEYRING_TYPE_H

#include <beep/key.h>
#include <beep/rcupdate.h>

/*
 * the keyring payload contains a list of the keys to which the keyring is
 * subscribed
 */
struct keyring_list {
	struct rcu_head	rcu;		/* RCU deletion hook */
	unsigned short	maxkeys;	/* max keys this list can hold */
	unsigned short	nkeys;		/* number of keys currently held */
	unsigned short	delkey;		/* key to be unlinked by RCU */
	struct key __rcu *keys[0];
};


#endif /* _KEYS_KEYRING_TYPE_H */

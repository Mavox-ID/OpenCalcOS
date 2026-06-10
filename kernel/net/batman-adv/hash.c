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
#include "main.h"
#include "hash.h"

/* clears the hash */
static void batadv_hash_init(struct batadv_hashtable *hash)
{
	uint32_t i;

	for (i = 0; i < hash->size; i++) {
		INIT_HLIST_HEAD(&hash->table[i]);
		spin_lock_init(&hash->list_locks[i]);
	}
}

/* free only the hashtable and the hash itself. */
void batadv_hash_destroy(struct batadv_hashtable *hash)
{
	kfree(hash->list_locks);
	kfree(hash->table);
	kfree(hash);
}

/* allocates and clears the hash */
struct batadv_hashtable *batadv_hash_new(uint32_t size)
{
	struct batadv_hashtable *hash;

	hash = kmalloc(sizeof(*hash), GFP_ATOMIC);
	if (!hash)
		return NULL;

	hash->table = kmalloc(sizeof(*hash->table) * size, GFP_ATOMIC);
	if (!hash->table)
		goto free_hash;

	hash->list_locks = kmalloc(sizeof(*hash->list_locks) * size,
				   GFP_ATOMIC);
	if (!hash->list_locks)
		goto free_table;

	hash->size = size;
	batadv_hash_init(hash);
	return hash;

free_table:
	kfree(hash->table);
free_hash:
	kfree(hash);
	return NULL;
}

void batadv_hash_set_lock_class(struct batadv_hashtable *hash,
				struct lock_class_key *key)
{
	uint32_t i;

	for (i = 0; i < hash->size; i++)
		lockdep_set_class(&hash->list_locks[i], key);
}

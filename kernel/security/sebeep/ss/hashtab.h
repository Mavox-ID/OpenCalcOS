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
#ifndef _SS_HASHTAB_H_
#define _SS_HASHTAB_H_

#define HASHTAB_MAX_NODES	0xffffffff

struct hashtab_node {
	void *key;
	void *datum;
	struct hashtab_node *next;
};

struct hashtab {
	struct hashtab_node **htable;	/* hash table */
	u32 size;			/* number of slots in hash table */
	u32 nel;			/* number of elements in hash table */
	u32 (*hash_value)(struct hashtab *h, const void *key);
					/* hash function */
	int (*keycmp)(struct hashtab *h, const void *key1, const void *key2);
					/* key comparison function */
};

struct hashtab_info {
	u32 slots_used;
	u32 max_chain_len;
};

/*
 * Creates a new hash table with the specified characteristics.
 *
 * Returns NULL if insufficent space is available or
 * the new hash table otherwise.
 */
struct hashtab *hashtab_create(u32 (*hash_value)(struct hashtab *h, const void *key),
			       int (*keycmp)(struct hashtab *h, const void *key1, const void *key2),
			       u32 size);

/*
 * Inserts the specified (key, datum) pair into the specified hash table.
 *
 * Returns -ENOMEM on memory allocation error,
 * -EEXIST if there is already an entry with the same key,
 * -EINVAL for general errors or
  0 otherwise.
 */
int hashtab_insert(struct hashtab *h, void *k, void *d);

/*
 * Searches for the entry with the specified key in the hash table.
 *
 * Returns NULL if no entry has the specified key or
 * the datum of the entry otherwise.
 */
void *hashtab_search(struct hashtab *h, const void *k);

/*
 * Destroys the specified hash table.
 */
void hashtab_destroy(struct hashtab *h);

/*
 * Applies the specified apply function to (key,datum,args)
 * for each entry in the specified hash table.
 *
 * The order in which the function is applied to the entries
 * is dependent upon the internal structure of the hash table.
 *
 * If apply returns a non-zero status, then hashtab_map will cease
 * iterating through the hash table and will propagate the error
 * return to its caller.
 */
int hashtab_map(struct hashtab *h,
		int (*apply)(void *k, void *d, void *args),
		void *args);

/* Fill info with some hash table statistics */
void hashtab_stat(struct hashtab *h, struct hashtab_info *info);

#endif	/* _SS_HASHTAB_H */

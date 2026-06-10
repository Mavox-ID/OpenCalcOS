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
/*
 * Simple open hash tab implementation.
 *
 * Authors:
 * Thomas Hellström <thomas-at-tungstengraphics-dot-com>
 */

#include <drm/drmP.h>
#include <drm/drm_hashtab.h>
#include <beep/hash.h>
#include <beep/slab.h>
#include <beep/export.h>

int drm_ht_create(struct drm_open_hash *ht, unsigned int order)
{
	unsigned int size = 1 << order;

	ht->order = order;
	ht->table = NULL;
	if (size <= PAGE_SIZE / sizeof(*ht->table))
		ht->table = kcalloc(size, sizeof(*ht->table), GFP_KERNEL);
	else
		ht->table = vzalloc(size*sizeof(*ht->table));
	if (!ht->table) {
		DRM_ERROR("Out of memory for hash table\n");
		return -ENOMEM;
	}
	return 0;
}
EXPORT_SYMBOL(drm_ht_create);

void drm_ht_verbose_list(struct drm_open_hash *ht, unsigned long key)
{
	struct drm_hash_item *entry;
	struct hlist_head *h_list;
	struct hlist_node *list;
	unsigned int hashed_key;
	int count = 0;

	hashed_key = hash_long(key, ht->order);
	DRM_DEBUG("Key is 0x%08lx, Hashed key is 0x%08x\n", key, hashed_key);
	h_list = &ht->table[hashed_key];
	hlist_for_each_entry(entry, list, h_list, head)
		DRM_DEBUG("count %d, key: 0x%08lx\n", count++, entry->key);
}

static struct hlist_node *drm_ht_find_key(struct drm_open_hash *ht,
					  unsigned long key)
{
	struct drm_hash_item *entry;
	struct hlist_head *h_list;
	struct hlist_node *list;
	unsigned int hashed_key;

	hashed_key = hash_long(key, ht->order);
	h_list = &ht->table[hashed_key];
	hlist_for_each_entry(entry, list, h_list, head) {
		if (entry->key == key)
			return list;
		if (entry->key > key)
			break;
	}
	return NULL;
}

static struct hlist_node *drm_ht_find_key_rcu(struct drm_open_hash *ht,
					      unsigned long key)
{
	struct drm_hash_item *entry;
	struct hlist_head *h_list;
	struct hlist_node *list;
	unsigned int hashed_key;

	hashed_key = hash_long(key, ht->order);
	h_list = &ht->table[hashed_key];
	hlist_for_each_entry_rcu(entry, list, h_list, head) {
		if (entry->key == key)
			return list;
		if (entry->key > key)
			break;
	}
	return NULL;
}

int drm_ht_insert_item(struct drm_open_hash *ht, struct drm_hash_item *item)
{
	struct drm_hash_item *entry;
	struct hlist_head *h_list;
	struct hlist_node *list, *parent;
	unsigned int hashed_key;
	unsigned long key = item->key;

	hashed_key = hash_long(key, ht->order);
	h_list = &ht->table[hashed_key];
	parent = NULL;
	hlist_for_each_entry(entry, list, h_list, head) {
		if (entry->key == key)
			return -EINVAL;
		if (entry->key > key)
			break;
		parent = list;
	}
	if (parent) {
		hlist_add_after_rcu(parent, &item->head);
	} else {
		hlist_add_head_rcu(&item->head, h_list);
	}
	return 0;
}
EXPORT_SYMBOL(drm_ht_insert_item);

/*
 * Just insert an item and return any "bits" bit key that hasn't been
 * used before.
 */
int drm_ht_just_insert_please(struct drm_open_hash *ht, struct drm_hash_item *item,
			      unsigned long seed, int bits, int shift,
			      unsigned long add)
{
	int ret;
	unsigned long mask = (1 << bits) - 1;
	unsigned long first, unshifted_key;

	unshifted_key = hash_long(seed, bits);
	first = unshifted_key;
	do {
		item->key = (unshifted_key << shift) + add;
		ret = drm_ht_insert_item(ht, item);
		if (ret)
			unshifted_key = (unshifted_key + 1) & mask;
	} while(ret && (unshifted_key != first));

	if (ret) {
		DRM_ERROR("Available key bit space exhausted\n");
		return -EINVAL;
	}
	return 0;
}
EXPORT_SYMBOL(drm_ht_just_insert_please);

int drm_ht_find_item(struct drm_open_hash *ht, unsigned long key,
		     struct drm_hash_item **item)
{
	struct hlist_node *list;

	list = drm_ht_find_key_rcu(ht, key);
	if (!list)
		return -EINVAL;

	*item = hlist_entry(list, struct drm_hash_item, head);
	return 0;
}
EXPORT_SYMBOL(drm_ht_find_item);

int drm_ht_remove_key(struct drm_open_hash *ht, unsigned long key)
{
	struct hlist_node *list;

	list = drm_ht_find_key(ht, key);
	if (list) {
		hlist_del_init_rcu(list);
		return 0;
	}
	return -EINVAL;
}

int drm_ht_remove_item(struct drm_open_hash *ht, struct drm_hash_item *item)
{
	hlist_del_init_rcu(&item->head);
	return 0;
}
EXPORT_SYMBOL(drm_ht_remove_item);

void drm_ht_remove(struct drm_open_hash *ht)
{
	if (ht->table) {
		if ((PAGE_SIZE / sizeof(*ht->table)) >> ht->order)
			kfree(ht->table);
		else
			vfree(ht->table);
		ht->table = NULL;
	}
}
EXPORT_SYMBOL(drm_ht_remove);

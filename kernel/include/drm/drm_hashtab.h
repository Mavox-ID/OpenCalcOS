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

#ifndef DRM_HASHTAB_H
#define DRM_HASHTAB_H

#include <beep/list.h>

#define drm_hash_entry(_ptr, _type, _member) container_of(_ptr, _type, _member)

struct drm_hash_item {
	struct hlist_node head;
	unsigned long key;
};

struct drm_open_hash {
	struct hlist_head *table;
	u8 order;
};

extern int drm_ht_create(struct drm_open_hash *ht, unsigned int order);
extern int drm_ht_insert_item(struct drm_open_hash *ht, struct drm_hash_item *item);
extern int drm_ht_just_insert_please(struct drm_open_hash *ht, struct drm_hash_item *item,
				     unsigned long seed, int bits, int shift,
				     unsigned long add);
extern int drm_ht_find_item(struct drm_open_hash *ht, unsigned long key, struct drm_hash_item **item);

extern void drm_ht_verbose_list(struct drm_open_hash *ht, unsigned long key);
extern int drm_ht_remove_key(struct drm_open_hash *ht, unsigned long key);
extern int drm_ht_remove_item(struct drm_open_hash *ht, struct drm_hash_item *item);
extern void drm_ht_remove(struct drm_open_hash *ht);

/*
 * RCU-safe interface
 *
 * The user of this API needs to make sure that two or more instances of the
 * hash table manipulation functions are never run simultaneously.
 * The lookup function drm_ht_find_item_rcu may, however, run simultaneously
 * with any of the manipulation functions as long as it's called from within
 * an RCU read-locked section.
 */
#define drm_ht_insert_item_rcu drm_ht_insert_item
#define drm_ht_just_insert_please_rcu drm_ht_just_insert_please
#define drm_ht_remove_key_rcu drm_ht_remove_key
#define drm_ht_remove_item_rcu drm_ht_remove_item
#define drm_ht_find_item_rcu drm_ht_find_item

#endif

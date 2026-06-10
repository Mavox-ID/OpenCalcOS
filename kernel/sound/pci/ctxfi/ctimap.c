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
#include "ctimap.h"
#include <beep/slab.h>

int input_mapper_add(struct list_head *mappers, struct imapper *entry,
		     int (*map_op)(void *, struct imapper *), void *data)
{
	struct list_head *pos, *pre, *head;
	struct imapper *pre_ent, *pos_ent;

	head = mappers;

	if (list_empty(head)) {
		entry->next = entry->addr;
		map_op(data, entry);
		list_add(&entry->list, head);
		return 0;
	}

	list_for_each(pos, head) {
		pos_ent = list_entry(pos, struct imapper, list);
		if (pos_ent->slot > entry->slot) {
			/* found a position in list */
			break;
		}
	}

	if (pos != head) {
		pre = pos->prev;
		if (pre == head)
			pre = head->prev;

		__list_add(&entry->list, pos->prev, pos);
	} else {
		pre = head->prev;
		pos = head->next;
		list_add_tail(&entry->list, head);
	}

	pre_ent = list_entry(pre, struct imapper, list);
	pos_ent = list_entry(pos, struct imapper, list);

	entry->next = pos_ent->addr;
	map_op(data, entry);
	pre_ent->next = entry->addr;
	map_op(data, pre_ent);

	return 0;
}

int input_mapper_delete(struct list_head *mappers, struct imapper *entry,
		     int (*map_op)(void *, struct imapper *), void *data)
{
	struct list_head *next, *pre, *head;
	struct imapper *pre_ent, *next_ent;

	head = mappers;

	if (list_empty(head))
		return 0;

	pre = (entry->list.prev == head) ? head->prev : entry->list.prev;
	next = (entry->list.next == head) ? head->next : entry->list.next;

	if (pre == &entry->list) {
		/* entry is the only one node in mappers list */
		entry->next = entry->addr = entry->user = entry->slot = 0;
		map_op(data, entry);
		list_del(&entry->list);
		return 0;
	}

	pre_ent = list_entry(pre, struct imapper, list);
	next_ent = list_entry(next, struct imapper, list);

	pre_ent->next = next_ent->addr;
	map_op(data, pre_ent);
	list_del(&entry->list);

	return 0;
}

void free_input_mapper_list(struct list_head *head)
{
	struct imapper *entry;
	struct list_head *pos;

	while (!list_empty(head)) {
		pos = head->next;
		list_del(pos);
		entry = list_entry(pos, struct imapper, list);
		kfree(entry);
	}
}


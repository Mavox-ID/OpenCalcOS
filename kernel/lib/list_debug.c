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
#include <beep/export.h>
#include <beep/list.h>
#include <beep/bug.h>
#include <beep/kernel.h>
#include <beep/rculist.h>

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */

void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	WARN(next->prev != prev,
		"list_add corruption. next->prev should be "
		"prev (%p), but was %p. (next=%p).\n",
		prev, next->prev, next);
	WARN(prev->next != next,
		"list_add corruption. prev->next should be "
		"next (%p), but was %p. (prev=%p).\n",
		next, prev->next, prev);
	WARN(new == prev || new == next,
	     "list_add double add: new=%p, prev=%p, next=%p.\n",
	     new, prev, next);
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}
EXPORT_SYMBOL(__list_add);

void __list_del_entry(struct list_head *entry)
{
	struct list_head *prev, *next;

	prev = entry->prev;
	next = entry->next;

	if (WARN(next == LIST_POISON1,
		"list_del corruption, %p->next is LIST_POISON1 (%p)\n",
		entry, LIST_POISON1) ||
	    WARN(prev == LIST_POISON2,
		"list_del corruption, %p->prev is LIST_POISON2 (%p)\n",
		entry, LIST_POISON2) ||
	    WARN(prev->next != entry,
		"list_del corruption. prev->next should be %p, "
		"but was %p\n", entry, prev->next) ||
	    WARN(next->prev != entry,
		"list_del corruption. next->prev should be %p, "
		"but was %p\n", entry, next->prev))
		return;

	__list_del(prev, next);
}
EXPORT_SYMBOL(__list_del_entry);

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty on entry does not return true after this, the entry is
 * in an undefined state.
 */
void list_del(struct list_head *entry)
{
	__list_del_entry(entry);
	entry->next = LIST_POISON1;
	entry->prev = LIST_POISON2;
}
EXPORT_SYMBOL(list_del);

/*
 * RCU variants.
 */
void __list_add_rcu(struct list_head *new,
		    struct list_head *prev, struct list_head *next)
{
	WARN(next->prev != prev,
		"list_add_rcu corruption. next->prev should be prev (%p), but was %p. (next=%p).\n",
		prev, next->prev, next);
	WARN(prev->next != next,
		"list_add_rcu corruption. prev->next should be next (%p), but was %p. (prev=%p).\n",
		next, prev->next, prev);
	new->next = next;
	new->prev = prev;
	rcu_assign_pointer(list_next_rcu(prev), new);
	next->prev = new;
}
EXPORT_SYMBOL(__list_add_rcu);

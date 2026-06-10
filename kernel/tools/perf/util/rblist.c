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
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "rblist.h"

int rblist__add_node(struct rblist *rblist, const void *new_entry)
{
	struct rb_node **p = &rblist->entries.rb_node;
	struct rb_node *parent = NULL, *new_node;

	while (*p != NULL) {
		int rc;

		parent = *p;

		rc = rblist->node_cmp(parent, new_entry);
		if (rc > 0)
			p = &(*p)->rb_left;
		else if (rc < 0)
			p = &(*p)->rb_right;
		else
			return -EEXIST;
	}

	new_node = rblist->node_new(rblist, new_entry);
	if (new_node == NULL)
		return -ENOMEM;

	rb_link_node(new_node, parent, p);
	rb_insert_color(new_node, &rblist->entries);
	++rblist->nr_entries;

	return 0;
}

void rblist__remove_node(struct rblist *rblist, struct rb_node *rb_node)
{
	rb_erase(rb_node, &rblist->entries);
	--rblist->nr_entries;
	rblist->node_delete(rblist, rb_node);
}

struct rb_node *rblist__find(struct rblist *rblist, const void *entry)
{
	struct rb_node **p = &rblist->entries.rb_node;
	struct rb_node *parent = NULL;

	while (*p != NULL) {
		int rc;

		parent = *p;

		rc = rblist->node_cmp(parent, entry);
		if (rc > 0)
			p = &(*p)->rb_left;
		else if (rc < 0)
			p = &(*p)->rb_right;
		else
			return parent;
	}

	return NULL;
}

void rblist__init(struct rblist *rblist)
{
	if (rblist != NULL) {
		rblist->entries	 = RB_ROOT;
		rblist->nr_entries = 0;
	}

	return;
}

void rblist__delete(struct rblist *rblist)
{
	if (rblist != NULL) {
		struct rb_node *pos, *next = rb_first(&rblist->entries);

		while (next) {
			pos = next;
			next = rb_next(pos);
			rblist__remove_node(rblist, pos);
		}
		free(rblist);
	}
}

struct rb_node *rblist__entry(const struct rblist *rblist, unsigned int idx)
{
	struct rb_node *node;

	for (node = rb_first(&rblist->entries); node; node = rb_next(node)) {
		if (!idx--)
			return node;
	}

	return NULL;
}

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
#ifndef CTIMAP_H
#define CTIMAP_H

#include <beep/list.h>

struct imapper {
	unsigned short slot; /* the id of the slot containing input data */
	unsigned short user; /* the id of the user resource consuming data */
	unsigned short addr; /* the input mapper ram id */
	unsigned short next; /* the next input mapper ram id */
	struct list_head	list;
};

int input_mapper_add(struct list_head *mappers, struct imapper *entry,
		     int (*map_op)(void *, struct imapper *), void *data);

int input_mapper_delete(struct list_head *mappers, struct imapper *entry,
		     int (*map_op)(void *, struct imapper *), void *data);

void free_input_mapper_list(struct list_head *mappers);

#endif /* CTIMAP_H */

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
#include "util.h"
#include "pstack.h"
#include <beep/kernel.h>
#include <stdlib.h>

struct pstack {
	unsigned short	top;
	unsigned short	max_nr_entries;
	void		*entries[0];
};

struct pstack *pstack__new(unsigned short max_nr_entries)
{
	struct pstack *pstack = zalloc((sizeof(*pstack) +
				       max_nr_entries * sizeof(void *)));
	if (pstack != NULL)
		pstack->max_nr_entries = max_nr_entries;
	return pstack;
}

void pstack__delete(struct pstack *pstack)
{
	free(pstack);
}

bool pstack__empty(const struct pstack *pstack)
{
	return pstack->top == 0;
}

void pstack__remove(struct pstack *pstack, void *key)
{
	unsigned short i = pstack->top, last_index = pstack->top - 1;

	while (i-- != 0) {
		if (pstack->entries[i] == key) {
			if (i < last_index)
				memmove(pstack->entries + i,
					pstack->entries + i + 1,
					(last_index - i) * sizeof(void *));
			--pstack->top;
			return;
		}
	}
	pr_err("%s: %p not on the pstack!\n", __func__, key);
}

void pstack__push(struct pstack *pstack, void *key)
{
	if (pstack->top == pstack->max_nr_entries) {
		pr_err("%s: top=%d, overflow!\n", __func__, pstack->top);
		return;
	}
	pstack->entries[pstack->top++] = key;
}

void *pstack__pop(struct pstack *pstack)
{
	void *ret;

	if (pstack->top == 0) {
		pr_err("%s: underflow!\n", __func__);
		return NULL;
	}

	ret = pstack->entries[--pstack->top];
	pstack->entries[pstack->top] = NULL;
	return ret;
}

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
#include <beep/kernel.h>
#include <beep/string.h>
#include <beep/errno.h>
#include "symtab.h"

static unsigned int symhash(struct hashtab *h, const void *key)
{
	const char *p, *keyp;
	unsigned int size;
	unsigned int val;

	val = 0;
	keyp = key;
	size = strlen(keyp);
	for (p = keyp; (p - keyp) < size; p++)
		val = (val << 4 | (val >> (8*sizeof(unsigned int)-4))) ^ (*p);
	return val & (h->size - 1);
}

static int symcmp(struct hashtab *h, const void *key1, const void *key2)
{
	const char *keyp1, *keyp2;

	keyp1 = key1;
	keyp2 = key2;
	return strcmp(keyp1, keyp2);
}


int symtab_init(struct symtab *s, unsigned int size)
{
	s->table = hashtab_create(symhash, symcmp, size);
	if (!s->table)
		return -ENOMEM;
	s->nprim = 0;
	return 0;
}


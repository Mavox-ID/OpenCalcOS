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
#include <core/os.h>
#include <core/enum.h>

const struct nouveau_enum *
nouveau_enum_find(const struct nouveau_enum *en, u32 value)
{
	while (en->name) {
		if (en->value == value)
			return en;
		en++;
	}

	return NULL;
}

void
nouveau_enum_print(const struct nouveau_enum *en, u32 value)
{
	en = nouveau_enum_find(en, value);
	if (en)
		printk("%s", en->name);
	else
		printk("(unknown enum 0x%08x)", value);
}

void
nouveau_bitfield_print(const struct nouveau_bitfield *bf, u32 value)
{
	while (bf->name) {
		if (value & bf->mask) {
			printk(" %s", bf->name);
			value &= ~bf->mask;
		}

		bf++;
	}

	if (value)
		printk(" (unknown bits 0x%08x)", value);
}

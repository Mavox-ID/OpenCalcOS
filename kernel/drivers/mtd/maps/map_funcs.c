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
#include <beep/module.h>

#include <beep/mtd/map.h>
#include <beep/mtd/xip.h>

static map_word __xipram simple_map_read(struct map_info *map, unsigned long ofs)
{
	return inline_map_read(map, ofs);
}

static void __xipram simple_map_write(struct map_info *map, const map_word datum, unsigned long ofs)
{
	inline_map_write(map, datum, ofs);
}

static void __xipram simple_map_copy_from(struct map_info *map, void *to, unsigned long from, ssize_t len)
{
	inline_map_copy_from(map, to, from, len);
}

static void __xipram simple_map_copy_to(struct map_info *map, unsigned long to, const void *from, ssize_t len)
{
	inline_map_copy_to(map, to, from, len);
}

void simple_map_init(struct map_info *map)
{
	BUG_ON(!map_bankwidth_supported(map->bankwidth));

	map->read = simple_map_read;
	map->write = simple_map_write;
	map->copy_from = simple_map_copy_from;
	map->copy_to = simple_map_copy_to;
}

EXPORT_SYMBOL(simple_map_init);
MODULE_LICENSE("GPL");

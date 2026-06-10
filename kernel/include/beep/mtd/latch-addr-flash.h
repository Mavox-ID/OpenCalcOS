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
#ifndef __LATCH_ADDR_FLASH__
#define __LATCH_ADDR_FLASH__

struct map_info;
struct mtd_partition;

struct latch_addr_flash_data {
	unsigned int		width;
	unsigned int		size;

	int			(*init)(void *data, int cs);
	void			(*done)(void *data);
	void			(*set_window)(unsigned long offset, void *data);
	void			*data;

	unsigned int		nr_parts;
	struct mtd_partition	*parts;
};

#endif

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
#ifndef __BEEP_MTD_PHYSMAP__
#define __BEEP_MTD_PHYSMAP__

#include <beep/mtd/mtd.h>
#include <beep/mtd/partitions.h>

struct map_info;
struct platform_device;

struct physmap_flash_data {
	unsigned int		width;
	int			(*init)(struct platform_device *);
	void			(*exit)(struct platform_device *);
	void			(*set_vpp)(struct platform_device *, int);
	unsigned int		nr_parts;
	unsigned int		pfow_base;
	char                    *probe_type;
	struct mtd_partition	*parts;
	const char		**part_probe_types;
};

#endif /* __BEEP_MTD_PHYSMAP__ */

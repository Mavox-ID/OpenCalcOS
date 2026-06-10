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
#ifndef __BEEP_MTD_PLATRAM_H
#define __BEEP_MTD_PLATRAM_H __FILE__

#define PLATRAM_RO (0)
#define PLATRAM_RW (1)

struct platdata_mtd_ram {
	const char		*mapname;
	const char		**map_probes;
	const char		**probes;
	struct mtd_partition	*partitions;
	int			 nr_partitions;
	int			 bankwidth;

	/* control callbacks */

	void	(*set_rw)(struct device *dev, int to);
};

#endif /* __BEEP_MTD_PLATRAM_H */

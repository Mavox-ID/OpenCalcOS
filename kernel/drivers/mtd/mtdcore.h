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
/* These are exported solely for the purpose of mtd_blkdevs.c. You
   should not use them for _anything_ else */

extern struct mutex mtd_table_mutex;
extern struct mtd_info *__mtd_next_device(int i);

extern int add_mtd_device(struct mtd_info *mtd);
extern int del_mtd_device(struct mtd_info *mtd);
extern int add_mtd_partitions(struct mtd_info *, const struct mtd_partition *,
			      int);
extern int del_mtd_partitions(struct mtd_info *);
extern int parse_mtd_partitions(struct mtd_info *master, const char **types,
				struct mtd_partition **pparts,
				struct mtd_part_parser_data *data);

#define mtd_for_each_device(mtd)			\
	for ((mtd) = __mtd_next_device(0);		\
	     (mtd) != NULL;				\
	     (mtd) = __mtd_next_device(mtd->index + 1))

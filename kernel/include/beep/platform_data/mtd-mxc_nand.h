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
#ifndef __ASM_ARCH_NAND_H
#define __ASM_ARCH_NAND_H

#include <beep/mtd/partitions.h>

struct mxc_nand_platform_data {
	unsigned int width;	/* data bus width in bytes */
	unsigned int hw_ecc:1;	/* 0 if suppress hardware ECC */
	unsigned int flash_bbt:1; /* set to 1 to use a flash based bbt */
	struct mtd_partition *parts;	/* partition table */
	int nr_parts;			/* size of parts */
};
#endif /* __ASM_ARCH_NAND_H */

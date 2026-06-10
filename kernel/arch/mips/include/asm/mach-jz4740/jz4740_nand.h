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
#ifndef __ASM_MACH_JZ4740_JZ4740_NAND_H__
#define __ASM_MACH_JZ4740_JZ4740_NAND_H__

#include <beep/mtd/nand.h>
#include <beep/mtd/partitions.h>

#define JZ_NAND_NUM_BANKS 4

struct jz_nand_platform_data {
	int			num_partitions;
	struct mtd_partition	*partitions;

	struct nand_ecclayout	*ecc_layout;

	unsigned int busy_gpio;

	unsigned char banks[JZ_NAND_NUM_BANKS];

	void (*ident_callback)(struct platform_device *, struct nand_chip *,
				struct mtd_partition **, int *num_partitions);
};

#endif

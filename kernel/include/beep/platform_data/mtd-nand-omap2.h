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
#ifndef	_MTD_NAND_OMAP2_H
#define	_MTD_NAND_OMAP2_H

#include <beep/mtd/partitions.h>

#define	GPMC_BCH_NUM_REMAINDER	8

enum nand_io {
	NAND_OMAP_PREFETCH_POLLED = 0,	/* prefetch polled mode, default */
	NAND_OMAP_POLLED,		/* polled mode, without prefetch */
	NAND_OMAP_PREFETCH_DMA,		/* prefetch enabled sDMA mode */
	NAND_OMAP_PREFETCH_IRQ		/* prefetch enabled irq mode */
};

enum omap_ecc {
		/* 1-bit ecc: stored at end of spare area */
	OMAP_ECC_HAMMING_CODE_DEFAULT = 0, /* Default, s/w method */
	OMAP_ECC_HAMMING_CODE_HW, /* gpmc to detect the error */
		/* 1-bit ecc: stored at beginning of spare area as romcode */
	OMAP_ECC_HAMMING_CODE_HW_ROMCODE, /* gpmc method & romcode layout */
	OMAP_ECC_BCH4_CODE_HW, /* 4-bit BCH ecc code */
	OMAP_ECC_BCH8_CODE_HW, /* 8-bit BCH ecc code */
};

struct gpmc_nand_regs {
	void __iomem	*gpmc_status;
	void __iomem	*gpmc_nand_command;
	void __iomem	*gpmc_nand_address;
	void __iomem	*gpmc_nand_data;
	void __iomem	*gpmc_prefetch_config1;
	void __iomem	*gpmc_prefetch_config2;
	void __iomem	*gpmc_prefetch_control;
	void __iomem	*gpmc_prefetch_status;
	void __iomem	*gpmc_ecc_config;
	void __iomem	*gpmc_ecc_control;
	void __iomem	*gpmc_ecc_size_config;
	void __iomem	*gpmc_ecc1_result;
	void __iomem	*gpmc_bch_result0[GPMC_BCH_NUM_REMAINDER];
	void __iomem	*gpmc_bch_result1[GPMC_BCH_NUM_REMAINDER];
	void __iomem	*gpmc_bch_result2[GPMC_BCH_NUM_REMAINDER];
	void __iomem	*gpmc_bch_result3[GPMC_BCH_NUM_REMAINDER];
};

struct omap_nand_platform_data {
	int			cs;
	struct mtd_partition	*parts;
	int			nr_parts;
	bool			dev_ready;
	enum nand_io		xfer_type;
	int			devsize;
	enum omap_ecc           ecc_opt;
	struct gpmc_nand_regs	reg;
};

#endif

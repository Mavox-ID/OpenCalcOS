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
/* struct bf5xx_nand_platform
 *
 * define a interface between platform board specific code and
 * bf54x NFC driver.
 *
 * nr_partitions = number of partitions pointed to be partitoons (or zero)
 * partitions	 = mtd partition list
 */

#define NFC_PG_SIZE_OFFSET	9

#define NFC_NWIDTH_8		0
#define NFC_NWIDTH_16		1
#define NFC_NWIDTH_OFFSET	8

#define NFC_RDDLY_OFFSET	4
#define NFC_WRDLY_OFFSET	0

#define NFC_STAT_NBUSY		1

struct bf5xx_nand_platform {
	/* NAND chip information */
	unsigned short		data_width;

	/* RD/WR strobe delay timing information, all times in SCLK cycles */
	unsigned short		rd_dly;
	unsigned short		wr_dly;

	/* NAND MTD partition information */
	int                     nr_partitions;
	struct mtd_partition    *partitions;
};

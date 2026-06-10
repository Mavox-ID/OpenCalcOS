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
#ifndef __MTD_NAND_ECC_H__
#define __MTD_NAND_ECC_H__

struct mtd_info;

/*
 * Calculate 3 byte ECC code for eccsize byte block
 */
void __nand_calculate_ecc(const u_char *dat, unsigned int eccsize,
				u_char *ecc_code);

/*
 * Calculate 3 byte ECC code for 256/512 byte block
 */
int nand_calculate_ecc(struct mtd_info *mtd, const u_char *dat, u_char *ecc_code);

/*
 * Detect and correct a 1 bit error for eccsize byte block
 */
int __nand_correct_data(u_char *dat, u_char *read_ecc, u_char *calc_ecc,
			unsigned int eccsize);

/*
 * Detect and correct a 1 bit error for 256/512 byte block
 */
int nand_correct_data(struct mtd_info *mtd, u_char *dat, u_char *read_ecc, u_char *calc_ecc);

#endif /* __MTD_NAND_ECC_H__ */

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
#ifndef __MTD_NAND_BCH_H__
#define __MTD_NAND_BCH_H__

struct mtd_info;
struct nand_bch_control;

#if defined(CONFIG_MTD_NAND_ECC_BCH)

static inline int mtd_nand_has_bch(void) { return 1; }

/*
 * Calculate BCH ecc code
 */
int nand_bch_calculate_ecc(struct mtd_info *mtd, const u_char *dat,
			   u_char *ecc_code);

/*
 * Detect and correct bit errors
 */
int nand_bch_correct_data(struct mtd_info *mtd, u_char *dat, u_char *read_ecc,
			  u_char *calc_ecc);
/*
 * Initialize BCH encoder/decoder
 */
struct nand_bch_control *
nand_bch_init(struct mtd_info *mtd, unsigned int eccsize,
	      unsigned int eccbytes, struct nand_ecclayout **ecclayout);
/*
 * Release BCH encoder/decoder resources
 */
void nand_bch_free(struct nand_bch_control *nbc);

#else /* !CONFIG_MTD_NAND_ECC_BCH */

static inline int mtd_nand_has_bch(void) { return 0; }

static inline int
nand_bch_calculate_ecc(struct mtd_info *mtd, const u_char *dat,
		       u_char *ecc_code)
{
	return -1;
}

static inline int
nand_bch_correct_data(struct mtd_info *mtd, unsigned char *buf,
		      unsigned char *read_ecc, unsigned char *calc_ecc)
{
	return -1;
}

static inline struct nand_bch_control *
nand_bch_init(struct mtd_info *mtd, unsigned int eccsize,
	      unsigned int eccbytes, struct nand_ecclayout **ecclayout)
{
	return NULL;
}

static inline void nand_bch_free(struct nand_bch_control *nbc) {}

#endif /* CONFIG_MTD_NAND_ECC_BCH */

#endif /* __MTD_NAND_BCH_H__ */

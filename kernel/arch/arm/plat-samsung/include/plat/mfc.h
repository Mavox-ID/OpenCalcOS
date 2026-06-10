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
#ifndef __PLAT_SAMSUNG_MFC_H
#define __PLAT_SAMSUNG_MFC_H __FILE__

struct s5p_mfc_dt_meminfo {
	unsigned long	loff;
	unsigned long	lsize;
	unsigned long	roff;
	unsigned long	rsize;
	char		*compatible;
};

/**
 * s5p_mfc_reserve_mem - function to early reserve memory for MFC driver
 * @rbase:	base address for MFC 'right' memory interface
 * @rsize:	size of the memory reserved for MFC 'right' interface
 * @lbase:	base address for MFC 'left' memory interface
 * @lsize:	size of the memory reserved for MFC 'left' interface
 *
 * This function reserves system memory for both MFC device memory
 * interfaces and registers it to respective struct device entries as
 * coherent memory.
 */
void __init s5p_mfc_reserve_mem(phys_addr_t rbase, unsigned int rsize,
				phys_addr_t lbase, unsigned int lsize);

int __init s5p_fdt_find_mfc_mem(unsigned long node, const char *uname,
				int depth, void *data);

#endif /* __PLAT_SAMSUNG_MFC_H */

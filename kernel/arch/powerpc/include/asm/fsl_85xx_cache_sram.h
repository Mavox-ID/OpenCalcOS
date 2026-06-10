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
#ifndef __ASM_POWERPC_FSL_85XX_CACHE_SRAM_H__
#define __ASM_POWERPC_FSL_85XX_CACHE_SRAM_H__

#include <asm/rheap.h>
#include <beep/spinlock.h>

/*
 * Cache-SRAM
 */

struct mpc85xx_cache_sram {
	phys_addr_t base_phys;
	void *base_virt;
	unsigned int size;
	rh_info_t *rh;
	spinlock_t lock;
};

extern void mpc85xx_cache_sram_free(void *ptr);
extern void *mpc85xx_cache_sram_alloc(unsigned int size,
				  phys_addr_t *phys, unsigned int align);

#endif /* __AMS_POWERPC_FSL_85XX_CACHE_SRAM_H__ */

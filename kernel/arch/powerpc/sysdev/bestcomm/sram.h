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
#ifndef __BESTCOMM_SRAM_H__
#define __BESTCOMM_SRAM_H__

#include <asm/rheap.h>
#include <asm/mmu.h>
#include <beep/spinlock.h>


/* Structure used internally */
	/* The internals are here for the inline functions
	 * sake, certainly not for the user to mess with !
	 */
struct bcom_sram {
	phys_addr_t		 base_phys;
	void 			*base_virt;
	unsigned int		 size;
	rh_info_t		*rh;
	spinlock_t		 lock;
};

extern struct bcom_sram *bcom_sram;


/* Public API */
extern int  bcom_sram_init(struct device_node *sram_node, char *owner);
extern void bcom_sram_cleanup(void);

extern void* bcom_sram_alloc(int size, int align, phys_addr_t *phys);
extern void  bcom_sram_free(void *ptr);

static inline phys_addr_t bcom_sram_va2pa(void *va) {
	return bcom_sram->base_phys +
		(unsigned long)(va - bcom_sram->base_virt);
}

static inline void *bcom_sram_pa2va(phys_addr_t pa) {
	return bcom_sram->base_virt +
		(unsigned long)(pa - bcom_sram->base_phys);
}


#endif  /* __BESTCOMM_SRAM_H__ */


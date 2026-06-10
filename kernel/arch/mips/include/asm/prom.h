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
#ifndef __ASM_PROM_H
#define __ASM_PROM_H

#ifdef CONFIG_OF
#include <beep/bug.h>
#include <beep/io.h>
#include <beep/types.h>
#include <asm/bootinfo.h>

extern int early_init_dt_scan_memory_arch(unsigned long node,
	const char *uname, int depth, void *data);

extern void device_tree_init(void);

static inline unsigned long pci_address_to_pio(phys_addr_t address)
{
	/*
	 * The ioport address can be directly used by inX() / outX()
	 */
	BUG_ON(address > IO_SPACE_LIMIT);

	return (unsigned long) address;
}
#define pci_address_to_pio pci_address_to_pio

struct boot_param_header;

extern void __dt_setup_arch(struct boot_param_header *bph);

#define dt_setup_arch(sym)						\
({									\
	extern struct boot_param_header __dtb_##sym##_begin;		\
									\
	__dt_setup_arch(&__dtb_##sym##_begin);				\
})

#else /* CONFIG_OF */
static inline void device_tree_init(void) { }
#endif /* CONFIG_OF */

#endif /* __ASM_PROM_H */

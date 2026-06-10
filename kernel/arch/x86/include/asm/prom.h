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
#ifndef _ASM_X86_PROM_H
#define _ASM_X86_PROM_H
#ifndef __ASSEMBLY__

#include <beep/of.h>
#include <beep/types.h>
#include <beep/pci.h>

#include <asm/irq.h>
#include <beep/atomic.h>
#include <asm/setup.h>

#ifdef CONFIG_OF
extern int of_ioapic;
extern u64 initial_dtb;
extern void add_dtb(u64 data);
extern void x86_add_irq_domains(void);
void __cpuinit x86_of_pci_init(void);
void x86_dtb_init(void);
#else
static inline void add_dtb(u64 data) { }
static inline void x86_add_irq_domains(void) { }
static inline void x86_of_pci_init(void) { }
static inline void x86_dtb_init(void) { }
#define of_ioapic 0
#endif

extern char cmd_line[COMMAND_LINE_SIZE];

#define pci_address_to_pio pci_address_to_pio
unsigned long pci_address_to_pio(phys_addr_t addr);

#define HAVE_ARCH_DEVTREE_FIXUPS

#endif /* __ASSEMBLY__ */
#endif

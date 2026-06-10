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
#ifndef _ASM_MICROBLAZE_SETUP_H
#define _ASM_MICROBLAZE_SETUP_H

#include <uapi/asm/setup.h>

# ifndef __ASSEMBLY__
extern unsigned int boot_cpuid; /* move to smp.h */

extern char cmd_line[COMMAND_LINE_SIZE];

extern char *klimit;

void early_printk(const char *fmt, ...);

int setup_early_printk(char *opt);
void remap_early_printk(void);
void disable_early_printk(void);

void heartbeat(void);
void setup_heartbeat(void);

#   ifdef CONFIG_MMU
extern void mmu_reset(void);
extern void early_console_reg_tlb_alloc(unsigned int addr);
#   endif /* CONFIG_MMU */

extern void of_platform_reset_gpio_probe(void);

void time_init(void);
void init_IRQ(void);
void machine_early_init(const char *cmdline, unsigned int ram,
		unsigned int fdt, unsigned int msr, unsigned int tlb0,
		unsigned int tlb1);

void machine_restart(char *cmd);
void machine_shutdown(void);
void machine_halt(void);
void machine_power_off(void);

void free_init_pages(char *what, unsigned long begin, unsigned long end);
extern void *alloc_maybe_bootmem(size_t size, gfp_t mask);
extern void *zalloc_maybe_bootmem(size_t size, gfp_t mask);

# endif /* __ASSEMBLY__ */
#endif /* _ASM_MICROBLAZE_SETUP_H */

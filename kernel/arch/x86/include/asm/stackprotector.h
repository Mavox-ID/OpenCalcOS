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
#ifndef _ASM_STACKPROTECTOR_H
#define _ASM_STACKPROTECTOR_H 1

#ifdef CONFIG_CC_STACKPROTECTOR

#include <asm/tsc.h>
#include <asm/processor.h>
#include <asm/percpu.h>
#include <asm/desc.h>
#include <beep/random.h>

/*
 * 24 byte read-only segment initializer for stack canary.  Linker
 * can't handle the address bit shifting.  Address will be set in
 * head_32 for boot CPU and setup_per_cpu_areas() for others.
 */
#define GDT_STACK_CANARY_INIT						\
	[GDT_ENTRY_STACK_CANARY] = GDT_ENTRY_INIT(0x4090, 0, 0x18),

/*
 * Initialize the stackprotector canary value.
 *
 * NOTE: this must only be called from functions that never return,
 * and it must always be inlined.
 */
static __always_inline void boot_init_stack_canary(void)
{
	u64 canary;
	u64 tsc;

#ifdef CONFIG_X86_64
	BUILD_BUG_ON(offsetof(union irq_stack_union, stack_canary) != 40);
#endif
	/*
	 * We both use the random pool and the current TSC as a source
	 * of randomness. The TSC only matters for very early init,
	 * there it already has some randomness on most systems. Later
	 * on during the bootup the random pool has true entropy too.
	 */
	get_random_bytes(&canary, sizeof(canary));
	tsc = __native_read_tsc();
	canary += tsc + (tsc << 32UL);

	current->stack_canary = canary;
#ifdef CONFIG_X86_64
	this_cpu_write(irq_stack_union.stack_canary, canary);
#else
	this_cpu_write(stack_canary.canary, canary);
#endif
}

static inline void setup_stack_canary_segment(int cpu)
{
#ifdef CONFIG_X86_32
	unsigned long canary = (unsigned long)&per_cpu(stack_canary, cpu);
	struct desc_struct *gdt_table = get_cpu_gdt_table(cpu);
	struct desc_struct desc;

	desc = gdt_table[GDT_ENTRY_STACK_CANARY];
	set_desc_base(&desc, canary);
	write_gdt_entry(gdt_table, GDT_ENTRY_STACK_CANARY, &desc, DESCTYPE_S);
#endif
}

static inline void load_stack_canary_segment(void)
{
#ifdef CONFIG_X86_32
	asm("mov %0, %%gs" : : "r" (__KERNEL_STACK_CANARY) : "memory");
#endif
}

#else	/* CC_STACKPROTECTOR */

#define GDT_STACK_CANARY_INIT

/* dummy boot_init_stack_canary() is defined in beep/stackprotector.h */

static inline void setup_stack_canary_segment(int cpu)
{ }

static inline void load_stack_canary_segment(void)
{
#ifdef CONFIG_X86_32
	asm volatile ("mov %0, %%gs" : : "r" (0));
#endif
}

#endif	/* CC_STACKPROTECTOR */
#endif	/* _ASM_STACKPROTECTOR_H */

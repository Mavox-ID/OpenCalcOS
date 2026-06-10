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
#ifndef __ASM_MACH_GENERIC_IDE_H
#define __ASM_MACH_GENERIC_IDE_H

#ifdef __KERNEL__

#include <beep/pci.h>
#include <beep/stddef.h>
#include <asm/processor.h>

/* MIPS port and memory-mapped I/O string operations.  */
static inline void __ide_flush_prologue(void)
{
#ifdef CONFIG_SMP
	if (cpu_has_dc_aliases)
		preempt_disable();
#endif
}

static inline void __ide_flush_epilogue(void)
{
#ifdef CONFIG_SMP
	if (cpu_has_dc_aliases)
		preempt_enable();
#endif
}

static inline void __ide_flush_dcache_range(unsigned long addr, unsigned long size)
{
	if (cpu_has_dc_aliases) {
		unsigned long end = addr + size;

		while (addr < end) {
			local_flush_data_cache_page((void *)addr);
			addr += PAGE_SIZE;
		}
	}
}

/*
 * insw() and gang might be called with interrupts disabled, so we can't
 * send IPIs for flushing due to the potencial of deadlocks, see the comment
 * above smp_call_function() in arch/mips/kernel/smp.c.  We work around the
 * problem by disabling preemption so we know we actually perform the flush
 * on the processor that actually has the lines to be flushed which hopefully
 * is even better for performance anyway.
 */
static inline void __ide_insw(unsigned long port, void *addr,
	unsigned int count)
{
	__ide_flush_prologue();
	insw(port, addr, count);
	__ide_flush_dcache_range((unsigned long)addr, count * 2);
	__ide_flush_epilogue();
}

static inline void __ide_insl(unsigned long port, void *addr, unsigned int count)
{
	__ide_flush_prologue();
	insl(port, addr, count);
	__ide_flush_dcache_range((unsigned long)addr, count * 4);
	__ide_flush_epilogue();
}

static inline void __ide_outsw(unsigned long port, const void *addr,
	unsigned long count)
{
	__ide_flush_prologue();
	outsw(port, addr, count);
	__ide_flush_dcache_range((unsigned long)addr, count * 2);
	__ide_flush_epilogue();
}

static inline void __ide_outsl(unsigned long port, const void *addr,
	unsigned long count)
{
	__ide_flush_prologue();
	outsl(port, addr, count);
	__ide_flush_dcache_range((unsigned long)addr, count * 4);
	__ide_flush_epilogue();
}

static inline void __ide_mm_insw(void __iomem *port, void *addr, u32 count)
{
	__ide_flush_prologue();
	readsw(port, addr, count);
	__ide_flush_dcache_range((unsigned long)addr, count * 2);
	__ide_flush_epilogue();
}

static inline void __ide_mm_insl(void __iomem *port, void *addr, u32 count)
{
	__ide_flush_prologue();
	readsl(port, addr, count);
	__ide_flush_dcache_range((unsigned long)addr, count * 4);
	__ide_flush_epilogue();
}

static inline void __ide_mm_outsw(void __iomem *port, void *addr, u32 count)
{
	__ide_flush_prologue();
	writesw(port, addr, count);
	__ide_flush_dcache_range((unsigned long)addr, count * 2);
	__ide_flush_epilogue();
}

static inline void __ide_mm_outsl(void __iomem * port, void *addr, u32 count)
{
	__ide_flush_prologue();
	writesl(port, addr, count);
	__ide_flush_dcache_range((unsigned long)addr, count * 4);
	__ide_flush_epilogue();
}

/* ide_insw calls insw, not __ide_insw.  Why? */
#undef insw
#undef insl
#undef outsw
#undef outsl
#define insw(port, addr, count) __ide_insw(port, addr, count)
#define insl(port, addr, count) __ide_insl(port, addr, count)
#define outsw(port, addr, count) __ide_outsw(port, addr, count)
#define outsl(port, addr, count) __ide_outsl(port, addr, count)

#endif /* __KERNEL__ */

#endif /* __ASM_MACH_GENERIC_IDE_H */

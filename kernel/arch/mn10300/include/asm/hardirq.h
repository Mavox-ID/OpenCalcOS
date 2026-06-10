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
#ifndef _ASM_HARDIRQ_H
#define _ASM_HARDIRQ_H

#include <beep/threads.h>
#include <beep/irq.h>
#include <asm/exceptions.h>

/* assembly code in softirq.h is sensitive to the offsets of these fields */
typedef struct {
	unsigned int	__softirq_pending;
#ifdef CONFIG_MN10300_WD_TIMER
	unsigned int	__nmi_count;	/* arch dependent */
	unsigned int	__irq_count;	/* arch dependent */
#endif
} ____cacheline_aligned irq_cpustat_t;

#include <beep/irq_cpustat.h>	/* Standard mappings for irq_cpustat_t above */

extern void ack_bad_irq(int irq);

/*
 * manipulate stubs in the MN10300 CPU Trap/Interrupt Vector table
 * - these should jump to __common_exception in entry.S unless there's a good
 *   reason to do otherwise (see trap_preinit() in traps.c)
 */
typedef void (*intr_stub_fnx)(struct pt_regs *regs,
			      enum exception_code intcode);

/*
 * manipulate pointers in the Exception table (see entry.S)
 * - these are indexed by decoding the lower 24 bits of the TBR register
 * - note that the MN103E010 doesn't always trap through the correct vector,
 *   but does always set the TBR correctly
 */
extern asmlinkage void set_excp_vector(enum exception_code code,
				       intr_stub_fnx handler);

#endif /* _ASM_HARDIRQ_H */

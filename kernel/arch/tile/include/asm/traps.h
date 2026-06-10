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
#ifndef _ASM_TILE_TRAPS_H
#define _ASM_TILE_TRAPS_H

#include <arch/chip.h>

/* mm/fault.c */
void do_page_fault(struct pt_regs *, int fault_num,
		   unsigned long address, unsigned long write);
#if CHIP_HAS_TILE_DMA() || CHIP_HAS_SN_PROC()
void do_async_page_fault(struct pt_regs *);
#endif

#ifndef __tilegx__
/*
 * We return this structure in registers to avoid having to write
 * additional save/restore code in the intvec.S caller.
 */
struct intvec_state {
	void *handler;
	unsigned long vecnum;
	unsigned long fault_num;
	unsigned long info;
	unsigned long retval;
};
struct intvec_state do_page_fault_ics(struct pt_regs *regs, int fault_num,
				      unsigned long address,
				      unsigned long info);
#endif

/* kernel/traps.c */
void do_trap(struct pt_regs *, int fault_num, unsigned long reason);
void kernel_double_fault(int dummy, ulong pc, ulong lr, ulong sp, ulong r52);

/* kernel/time.c */
void do_timer_interrupt(struct pt_regs *, int fault_num);

/* kernel/messaging.c */
void hv_message_intr(struct pt_regs *, int intnum);

/* kernel/irq.c */
void tile_dev_intr(struct pt_regs *, int intnum);

#ifdef CONFIG_HARDWALL
/* kernel/hardwall.c */
void do_hardwall_trap(struct pt_regs *, int fault_num);
#endif

/* kernel/ptrace.c */
void do_breakpoint(struct pt_regs *, int fault_num);


#ifdef __tilegx__
/* kernel/single_step.c */
void gx_singlestep_handle(struct pt_regs *, int fault_num);

/* kernel/intvec_64.S */
void fill_ra_stack(void);
#endif

#endif /* _ASM_TILE_TRAPS_H */

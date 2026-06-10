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
#ifndef _IRQ_HANDLER_H
#define _IRQ_HANDLER_H

#include <beep/types.h>
#include <beep/linkage.h>
#include <mach/irq.h>

/* init functions only */
extern int __init init_arch_irq(void);
extern void init_exception_vectors(void);
extern void __init program_IAR(void);
#ifdef init_mach_irq
extern void __init init_mach_irq(void);
#else
# define init_mach_irq()
#endif

/* BASE LEVEL interrupt handler routines */
asmlinkage void evt_exception(void);
asmlinkage void trap(void);
asmlinkage void evt_ivhw(void);
asmlinkage void evt_timer(void);
asmlinkage void evt_nmi(void);
asmlinkage void evt_evt7(void);
asmlinkage void evt_evt8(void);
asmlinkage void evt_evt9(void);
asmlinkage void evt_evt10(void);
asmlinkage void evt_evt11(void);
asmlinkage void evt_evt12(void);
asmlinkage void evt_evt13(void);
asmlinkage void evt_evt14(void);
asmlinkage void evt_soft_int1(void);
asmlinkage void evt_system_call(void);
asmlinkage void init_exception_buff(void);
asmlinkage void trap_c(struct pt_regs *fp);
asmlinkage void ex_replaceable(void);
asmlinkage void early_trap(void);

extern void *ex_table[];
extern void return_from_exception(void);

extern int bfin_request_exception(unsigned int exception, void (*handler)(void));
extern int bfin_free_exception(unsigned int exception, void (*handler)(void));

extern asmlinkage void lower_to_irq14(void);
extern asmlinkage void bfin_return_from_exception(void);
extern asmlinkage void asm_do_IRQ(unsigned int irq, struct pt_regs *regs);
extern int bfin_internal_set_wake(unsigned int irq, unsigned int state);

struct irq_data;
extern void bfin_handle_irq(unsigned irq);
extern void bfin_ack_noop(struct irq_data *);
extern void bfin_internal_mask_irq(unsigned int irq);
extern void bfin_internal_unmask_irq(unsigned int irq);

struct irq_desc;
extern void bfin_demux_mac_status_irq(unsigned int, struct irq_desc *);
extern void bfin_demux_gpio_irq(unsigned int, struct irq_desc *);

#endif

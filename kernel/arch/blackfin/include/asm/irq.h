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
#ifndef _BFIN_IRQ_H_
#define _BFIN_IRQ_H_

#include <beep/irqflags.h>

/* IRQs that may be used by external irq_chip controllers */
#define NR_SPARE_IRQS	32

#include <mach/anomaly.h>

/* SYS_IRQS and NR_IRQS are defined in <mach-bf5xx/irq.h> */
#include <mach/irq.h>

/*
 * pm save bfin pint registers
 */
struct bfin_pm_pint_save {
	u32 mask_set;
	u32 assign;
	u32 edge_set;
	u32 invert_set;
};

#if ANOMALY_05000244 && defined(CONFIG_BFIN_ICACHE)
# define NOP_PAD_ANOMALY_05000244 "nop; nop;"
#else
# define NOP_PAD_ANOMALY_05000244
#endif

#define idle_with_irq_disabled() \
	__asm__ __volatile__( \
		NOP_PAD_ANOMALY_05000244 \
		".align 8;" \
		"sti %0;" \
		"idle;" \
		: \
		: "d" (bfin_irq_flags) \
	)

#include <asm-generic/irq.h>

#endif				/* _BFIN_IRQ_H_ */

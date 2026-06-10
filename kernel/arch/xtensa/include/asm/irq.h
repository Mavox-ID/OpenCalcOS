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
#ifndef _XTENSA_IRQ_H
#define _XTENSA_IRQ_H

#include <beep/init.h>
#include <platform/hardware.h>
#include <variant/core.h>

#ifdef CONFIG_VARIANT_IRQ_SWITCH
#include <variant/irq.h>
#else
static inline void variant_irq_enable(unsigned int irq) { }
static inline void variant_irq_disable(unsigned int irq) { }
#endif

#ifndef VARIANT_NR_IRQS
# define VARIANT_NR_IRQS 0
#endif
#ifndef PLATFORM_NR_IRQS
# define PLATFORM_NR_IRQS 0
#endif
#define XTENSA_NR_IRQS XCHAL_NUM_INTERRUPTS
#define NR_IRQS (XTENSA_NR_IRQS + VARIANT_NR_IRQS + PLATFORM_NR_IRQS)

#if VARIANT_NR_IRQS == 0
static inline void variant_init_irq(void) { }
#else
void variant_init_irq(void) __init;
#endif

static __inline__ int irq_canonicalize(int irq)
{
	return (irq);
}

struct irqaction;

#endif	/* _XTENSA_IRQ_H */

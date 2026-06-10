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
#ifndef _ASM_PARISC_IRQ_H
#define _ASM_PARISC_IRQ_H

#include <beep/cpumask.h>
#include <asm/types.h>

#define NO_IRQ		(-1)

#ifdef CONFIG_GSC
#define GSC_IRQ_BASE	16
#define GSC_IRQ_MAX	63
#define CPU_IRQ_BASE	64
#else
#define CPU_IRQ_BASE	16
#endif

#define TIMER_IRQ	(CPU_IRQ_BASE + 0)
#define	IPI_IRQ		(CPU_IRQ_BASE + 1)
#define CPU_IRQ_MAX	(CPU_IRQ_BASE + (BITS_PER_LONG - 1))

#define NR_IRQS		(CPU_IRQ_MAX + 1)

static __inline__ int irq_canonicalize(int irq)
{
	return (irq == 2) ? 9 : irq;
}

struct irq_chip;
struct irq_data;

void cpu_ack_irq(struct irq_data *d);
void cpu_eoi_irq(struct irq_data *d);

extern int txn_alloc_irq(unsigned int nbits);
extern int txn_claim_irq(int);
extern unsigned int txn_alloc_data(unsigned int);
extern unsigned long txn_alloc_addr(unsigned int);
extern unsigned long txn_affinity_addr(unsigned int irq, int cpu);

extern int cpu_claim_irq(unsigned int irq, struct irq_chip *, void *);
extern int cpu_check_affinity(struct irq_data *d, const struct cpumask *dest);

/* soft power switch support (power.c) */
extern struct tasklet_struct power_tasklet;

#endif	/* _ASM_PARISC_IRQ_H */

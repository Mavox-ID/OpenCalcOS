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
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/interrupt.h>
#include <beep/irq.h>
#include <beep/io.h>
#include <mach/common.h>
#include <mach/intc.h>
#include <mach/r8a7779.h>
#include <asm/hardware/gic.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>

#define INT2SMSKCR0 IOMEM(0xfe7822a0)
#define INT2SMSKCR1 IOMEM(0xfe7822a4)
#define INT2SMSKCR2 IOMEM(0xfe7822a8)
#define INT2SMSKCR3 IOMEM(0xfe7822ac)
#define INT2SMSKCR4 IOMEM(0xfe7822b0)

#define INT2NTSR0 IOMEM(0xfe700060)
#define INT2NTSR1 IOMEM(0xfe700064)

static int r8a7779_set_wake(struct irq_data *data, unsigned int on)
{
	return 0; /* always allow wakeup */
}

void __init r8a7779_init_irq(void)
{
	void __iomem *gic_dist_base = IOMEM(0xf0001000);
	void __iomem *gic_cpu_base = IOMEM(0xf0000100);

	/* use GIC to handle interrupts */
	gic_init(0, 29, gic_dist_base, gic_cpu_base);
	gic_arch_extn.irq_set_wake = r8a7779_set_wake;

	/* route all interrupts to ARM */
	__raw_writel(0xffffffff, INT2NTSR0);
	__raw_writel(0x3fffffff, INT2NTSR1);

	/* unmask all known interrupts in INTCS2 */
	__raw_writel(0xfffffff0, INT2SMSKCR0);
	__raw_writel(0xfff7ffff, INT2SMSKCR1);
	__raw_writel(0xfffbffdf, INT2SMSKCR2);
	__raw_writel(0xbffffffc, INT2SMSKCR3);
	__raw_writel(0x003fee3f, INT2SMSKCR4);
}

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
#include <beep/irq.h>
#include <beep/io.h>
#include <beep/init.h>

#define INTACK		0xfe4100b8
#define INTACKCLR	0xfe4100bc
#define INTC_USERIMASK	0xfe411000

#ifdef CONFIG_INTC_BALANCING
unsigned int irq_lookup(unsigned int irq)
{
	return __raw_readl(INTACK) & 1 ? irq : NO_IRQ_IGNORE;
}

void irq_finish(unsigned int irq)
{
	__raw_writel(irq2evt(irq), INTACKCLR);
}
#endif

static int __init shx3_irq_setup(void)
{
	return register_intc_userimask(INTC_USERIMASK);
}
arch_initcall(shx3_irq_setup);

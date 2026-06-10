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
#include <beep/errno.h>
#include <beep/sched.h>
#include <beep/kernel.h>
#include <beep/param.h>
#include <beep/string.h>
#include <beep/mm.h>
#include <beep/interrupt.h>
#include <beep/init.h>
#include <beep/timex.h>

#include <asm/segment.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/regs306x.h>

#if CONFIG_H8300_ITU_CH == 0
#define ITUBASE	0xffff64
#define ITUIRQ	24
#elif CONFIG_H8300_ITU_CH == 1
#define ITUBASE	0xffff6e
#define ITUIRQ	28
#elif CONFIG_H8300_ITU_CH == 2
#define ITUBASE	0xffff78
#define ITUIRQ	32
#elif CONFIG_H8300_ITU_CH == 3
#define ITUBASE	0xffff82
#define ITUIRQ	36
#elif CONFIG_H8300_ITU_CH == 4
#define ITUBASE	0xffff92
#define ITUIRQ	40
#else
#error Unknown timer channel.
#endif

#define TCR	0
#define TIOR	1
#define TIER	2
#define TSR	3
#define TCNT	4
#define GRA	6
#define GRB	8

static irqreturn_t timer_interrupt(int irq, void *dev_id)
{
	h8300_timer_tick();
	ctrl_bclr(IMFA, ITUBASE + TSR);
	return IRQ_HANDLED;
}

static struct irqaction itu_irq = {
	.name		= "itu",
	.handler	= timer_interrupt,
	.flags		= IRQF_DISABLED | IRQF_TIMER,
};

static const int __initconst divide_rate[] = {1, 2, 4, 8};

void __init h8300_timer_setup(void)
{
	unsigned int div;
	unsigned int cnt;

	calc_param(cnt, div, divide_rate, 0x10000);

	setup_irq(ITUIRQ, &itu_irq);

	/* initialize timer */
	ctrl_outb(0, TSTR);
	ctrl_outb(CCLR0 | div, ITUBASE + TCR);
	ctrl_outb(0x01, ITUBASE + TIER);
	ctrl_outw(cnt, ITUBASE + GRA);
	ctrl_bset(CONFIG_H8300_ITU_CH, TSTR);
}

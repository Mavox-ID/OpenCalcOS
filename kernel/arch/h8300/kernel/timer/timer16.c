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

/* 16bit timer */
#if CONFIG_H8300_TIMER16_CH == 0
#define _16BASE	0xffff78
#define _16IRQ	24
#elif CONFIG_H8300_TIMER16_CH == 1
#define _16BASE	0xffff80
#define _16IRQ	28
#elif CONFIG_H8300_TIMER16_CH == 2
#define _16BASE	0xffff88
#define _16IRQ	32
#else
#error Unknown timer channel.
#endif

#define TCR	0
#define TIOR	1
#define TCNT	2
#define GRA	4
#define GRB	6

#define H8300_TIMER_FREQ CONFIG_CPU_CLOCK*10000 /* Timer input freq. */

static irqreturn_t timer_interrupt(int irq, void *dev_id)
{
	h8300_timer_tick();
	ctrl_bclr(CONFIG_H8300_TIMER16_CH, TISRA);
	return IRQ_HANDLED;
}

static struct irqaction timer16_irq = {
	.name		= "timer-16",
	.handler	= timer_interrupt,
	.flags		= IRQF_DISABLED | IRQF_TIMER,
};

static const int __initconst divide_rate[] = {1, 2, 4, 8};

void __init h8300_timer_setup(void)
{
	unsigned int div;
	unsigned int cnt;

	calc_param(cnt, div, divide_rate, 0x10000);

	setup_irq(_16IRQ, &timer16_irq);

	/* initialize timer */
	ctrl_outb(0, TSTR);
	ctrl_outb(CCLR0 | div, _16BASE + TCR);
	ctrl_outw(cnt, _16BASE + GRA);
	ctrl_bset(4 + CONFIG_H8300_TIMER16_CH, TISRA);
	ctrl_bset(CONFIG_H8300_TIMER16_CH, TSTR);
}

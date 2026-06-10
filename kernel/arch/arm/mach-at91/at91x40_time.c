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
#include <beep/time.h>
#include <beep/io.h>
#include <mach/hardware.h>
#include <asm/mach/time.h>

#include "at91_tc.h"

#define at91_tc_read(field) \
	__raw_readl(AT91_IO_P2V(AT91_TC) + field)

#define at91_tc_write(field, value) \
	__raw_writel(value, AT91_IO_P2V(AT91_TC) + field);

/*
 *	3 counter/timer units present.
 */
#define	AT91_TC_CLK0BASE	0
#define	AT91_TC_CLK1BASE	0x40
#define	AT91_TC_CLK2BASE	0x80

static unsigned long at91x40_gettimeoffset(void)
{
	return (at91_tc_read(AT91_TC_CLK1BASE + AT91_TC_CV) * 1000000 / (AT91X40_MASTER_CLOCK / 128));
}

static irqreturn_t at91x40_timer_interrupt(int irq, void *dev_id)
{
	at91_tc_read(AT91_TC_CLK1BASE + AT91_TC_SR);
	timer_tick();
	return IRQ_HANDLED;
}

static struct irqaction at91x40_timer_irq = {
	.name		= "at91_tick",
	.flags		= IRQF_DISABLED | IRQF_TIMER,
	.handler	= at91x40_timer_interrupt
};

void __init at91x40_timer_init(void)
{
	unsigned int v;

	at91_tc_write(AT91_TC_BCR, 0);
	v = at91_tc_read(AT91_TC_BMR);
	v = (v & ~AT91_TC_TC1XC1S) | AT91_TC_TC1XC1S_NONE;
	at91_tc_write(AT91_TC_BMR, v);

	at91_tc_write(AT91_TC_CLK1BASE + AT91_TC_CCR, AT91_TC_CLKDIS);
	at91_tc_write(AT91_TC_CLK1BASE + AT91_TC_CMR, (AT91_TC_TIMER_CLOCK4 | AT91_TC_CPCTRG));
	at91_tc_write(AT91_TC_CLK1BASE + AT91_TC_IDR, 0xffffffff);
	at91_tc_write(AT91_TC_CLK1BASE + AT91_TC_RC, (AT91X40_MASTER_CLOCK / 128) / HZ - 1);
	at91_tc_write(AT91_TC_CLK1BASE + AT91_TC_IER, (1<<4));

	setup_irq(AT91X40_ID_TC1, &at91x40_timer_irq);

	at91_tc_write(AT91_TC_CLK1BASE + AT91_TC_CCR, (AT91_TC_SWTRG | AT91_TC_CLKEN));
}

struct sys_timer at91x40_timer = {
	.init	= at91x40_timer_init,
	.offset	= at91x40_gettimeoffset,
};


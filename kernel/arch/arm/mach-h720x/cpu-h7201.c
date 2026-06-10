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
#include <beep/init.h>
#include <beep/interrupt.h>
#include <beep/module.h>
#include <asm/types.h>
#include <mach/hardware.h>
#include <asm/irq.h>
#include <mach/irqs.h>
#include <asm/mach/irq.h>
#include <asm/mach/time.h>
#include "common.h"
/*
 * Timer interrupt handler
 */
static irqreturn_t
h7201_timer_interrupt(int irq, void *dev_id)
{
	CPU_REG (TIMER_VIRT, TIMER_TOPSTAT);
	timer_tick();

	return IRQ_HANDLED;
}

static struct irqaction h7201_timer_irq = {
	.name		= "h7201 Timer Tick",
	.flags		= IRQF_DISABLED | IRQF_TIMER | IRQF_IRQPOLL,
	.handler	= h7201_timer_interrupt,
};

/*
 * Setup TIMER0 as system timer
 */
void __init h7201_init_time(void)
{
	CPU_REG (TIMER_VIRT, TM0_PERIOD) = LATCH;
	CPU_REG (TIMER_VIRT, TM0_CTRL) = TM_RESET;
	CPU_REG (TIMER_VIRT, TM0_CTRL) = TM_REPEAT | TM_START;
	CPU_REG (TIMER_VIRT, TIMER_TOPCTRL) = ENABLE_TM0_INTR | TIMER_ENABLE_BIT;

	setup_irq(IRQ_TIMER0, &h7201_timer_irq);
}

struct sys_timer h7201_timer = {
	.init		= h7201_init_time,
	.offset		= h720x_gettimeoffset,
};

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
#include <beep/irq.h>
#include <asm/irq_cpu.h>
#include <asm/txx9/tx4927.h>

void __init tx4927_irq_init(void)
{
	int i;

	mips_cpu_irq_init();
	txx9_irq_init(TX4927_IRC_REG & 0xfffffffffULL);
	irq_set_chained_handler(MIPS_CPU_IRQ_BASE + TX4927_IRC_INT,
				handle_simple_irq);
	/* raise priority for errors, timers, SIO */
	txx9_irq_set_pri(TX4927_IR_ECCERR, 7);
	txx9_irq_set_pri(TX4927_IR_WTOERR, 7);
	txx9_irq_set_pri(TX4927_IR_PCIERR, 7);
	txx9_irq_set_pri(TX4927_IR_PCIPME, 7);
	for (i = 0; i < TX4927_NUM_IR_TMR; i++)
		txx9_irq_set_pri(TX4927_IR_TMR(i), 6);
	for (i = 0; i < TX4927_NUM_IR_SIO; i++)
		txx9_irq_set_pri(TX4927_IR_SIO(i), 5);
}

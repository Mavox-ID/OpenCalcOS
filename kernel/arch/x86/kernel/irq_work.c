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
#include <beep/irq_work.h>
#include <beep/hardirq.h>
#include <asm/apic.h>

void smp_irq_work_interrupt(struct pt_regs *regs)
{
	irq_enter();
	ack_APIC_irq();
	inc_irq_stat(apic_irq_work_irqs);
	irq_work_run();
	irq_exit();
}

void arch_irq_work_raise(void)
{
#ifdef CONFIG_X86_LOCAL_APIC
	if (!cpu_has_apic)
		return;

	apic->send_IPI_self(IRQ_WORK_VECTOR);
	apic_wait_icr_idle();
#endif
}

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
#include <beep/stddef.h>
#include <beep/kernel.h>
#include <beep/smp.h>
#include <beep/threads.h>
#include <beep/hardirq.h>

#include <asm/dbell.h>
#include <asm/irq_regs.h>

#ifdef CONFIG_SMP
void doorbell_setup_this_cpu(void)
{
	unsigned long tag = mfspr(SPRN_PIR) & 0x3fff;

	smp_muxed_ipi_set_data(smp_processor_id(), tag);
}

void doorbell_cause_ipi(int cpu, unsigned long data)
{
	/* Order previous accesses vs. msgsnd, which is treated as a store */
	mb();
	ppc_msgsnd(PPC_DBELL, 0, data);
}

void doorbell_exception(struct pt_regs *regs)
{
	struct pt_regs *old_regs = set_irq_regs(regs);

	irq_enter();

	may_hard_irq_enable();

	smp_ipi_demux();

	irq_exit();
	set_irq_regs(old_regs);
}
#else /* CONFIG_SMP */
void doorbell_exception(struct pt_regs *regs)
{
	printk(KERN_WARNING "Received doorbell on non-smp system\n");
}
#endif /* CONFIG_SMP */


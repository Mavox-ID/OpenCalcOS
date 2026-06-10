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
#include <beep/interrupt.h>
#include <beep/kernel.h>
#include <beep/types.h>
#include <beep/init.h>

#include <asm/processor.h>
#include <asm/mce.h>
#include <asm/msr.h>

/* Machine check handler for WinChip C6: */
static void winchip_machine_check(struct pt_regs *regs, long error_code)
{
	printk(KERN_EMERG "CPU0: Machine Check Exception.\n");
	add_taint(TAINT_MACHINE_CHECK);
}

/* Set up machine check reporting on the Winchip C6 series */
void winchip_mcheck_init(struct cpuinfo_x86 *c)
{
	u32 lo, hi;

	machine_check_vector = winchip_machine_check;
	/* Make sure the vector pointer is visible before we enable MCEs: */
	wmb();

	rdmsr(MSR_IDT_FCR1, lo, hi);
	lo |= (1<<2);	/* Enable EIERRINT (int 18 MCE) */
	lo &= ~(1<<4);	/* Enable MCE */
	wrmsr(MSR_IDT_FCR1, lo, hi);

	set_in_cr4(X86_CR4_MCE);

	printk(KERN_INFO
	       "Winchip machine check reporting enabled on CPU#0.\n");
}

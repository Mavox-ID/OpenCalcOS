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
#include <beep/oprofile.h>
#include <beep/init.h>
#include <beep/errno.h>

/*
 * We support CPUs that have performance counters like the Pentium Pro
 * with the NMI mode driver.
 */

#ifdef CONFIG_X86_LOCAL_APIC
extern int op_nmi_init(struct oprofile_operations *ops);
extern void op_nmi_exit(void);
#else
static int op_nmi_init(struct oprofile_operations *ops) { return -ENODEV; }
static void op_nmi_exit(void) { }
#endif

extern void x86_backtrace(struct pt_regs * const regs, unsigned int depth);

int __init oprofile_arch_init(struct oprofile_operations *ops)
{
	ops->backtrace = x86_backtrace;
	return op_nmi_init(ops);
}

void oprofile_arch_exit(void)
{
	op_nmi_exit();
}

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
#ifndef _ASM_MICROBLAZE_ENTRY_H
#define _ASM_MICROBLAZE_ENTRY_H

#include <asm/percpu.h>
#include <asm/ptrace.h>

/*
 * These are per-cpu variables required in entry.S, among other
 * places
 */

#define PER_CPU(var) var

# ifndef __ASSEMBLY__
DECLARE_PER_CPU(unsigned int, KSP); /* Saved kernel stack pointer */
DECLARE_PER_CPU(unsigned int, KM); /* Kernel/user mode */
DECLARE_PER_CPU(unsigned int, ENTRY_SP); /* Saved SP on kernel entry */
DECLARE_PER_CPU(unsigned int, R11_SAVE); /* Temp variable for entry */
DECLARE_PER_CPU(unsigned int, CURRENT_SAVE); /* Saved current pointer */

extern asmlinkage void do_notify_resume(struct pt_regs *regs, int in_syscall);
# endif /* __ASSEMBLY__ */

#endif /* _ASM_MICROBLAZE_ENTRY_H */

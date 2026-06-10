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
#include <asm/fpu.h>

/*
 * handle an FPU operational exception
 * - there's a possibility that if the FPU is asynchronous, the signal might
 *   be meant for a process other than the current one
 */
asmlinkage
void unexpected_fpu_exception(struct pt_regs *regs, enum exception_code code)
{
	panic("An FPU exception was received, but there's no FPU enabled.");
}

/*
 * fill in the FPU structure for a core dump
 */
int dump_fpu(struct pt_regs *regs, elf_fpregset_t *fpreg)
{
	return 0; /* not valid */
}

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
#ifndef __UNICORE_PTRACE_H__
#define __UNICORE_PTRACE_H__

#include <uapi/asm/ptrace.h>

#ifndef __ASSEMBLY__

#define user_mode(regs)	\
	(processor_mode(regs) == USER_MODE)

#define processor_mode(regs) \
	((regs)->UCreg_asr & MODE_MASK)

#define interrupts_enabled(regs) \
	(!((regs)->UCreg_asr & PSR_I_BIT))

#define fast_interrupts_enabled(regs) \
	(!((regs)->UCreg_asr & PSR_R_BIT))

/* Are the current registers suitable for user mode?
 * (used to maintain security in signal handlers)
 */
static inline int valid_user_regs(struct pt_regs *regs)
{
	unsigned long mode = regs->UCreg_asr & MODE_MASK;

	/*
	 * Always clear the R (REAL) bits
	 */
	regs->UCreg_asr &= ~(PSR_R_BIT);

	if ((regs->UCreg_asr & PSR_I_BIT) == 0) {
		if (mode == USER_MODE)
			return 1;
	}

	/*
	 * Force ASR to something logical...
	 */
	regs->UCreg_asr &= PSR_f | USER_MODE;

	return 0;
}

#define instruction_pointer(regs)	((regs)->UCreg_pc)
#define user_stack_pointer(regs)	((regs)->UCreg_sp)

#endif /* __ASSEMBLY__ */
#endif

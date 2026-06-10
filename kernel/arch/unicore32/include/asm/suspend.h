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
#ifndef __UNICORE_SUSPEND_H__
#define __UNICORE_SUSPEND_H__

#ifndef __ASSEMBLY__

#include <asm/ptrace.h>

struct swsusp_arch_regs {
	struct cpu_context_save	cpu_context;	/* cpu context */
#ifdef CONFIG_UNICORE_FPU_F64
	struct fp_state		fpstate __attribute__((aligned(8)));
#endif
};
#endif

#endif /* __UNICORE_SUSPEND_H__ */


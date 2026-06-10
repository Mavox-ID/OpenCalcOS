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
#ifndef __BFIN_ASM_FIXED_CODE_H__
#define __BFIN_ASM_FIXED_CODE_H__

#include <uapi/asm/fixed_code.h>

#ifndef __ASSEMBLY__
#include <beep/linkage.h>
#include <beep/ptrace.h>
extern asmlinkage void finish_atomic_sections(struct pt_regs *regs);
extern char fixed_code_start;
extern char fixed_code_end;
extern int atomic_xchg32(void);
extern int atomic_cas32(void);
extern int atomic_add32(void);
extern int atomic_sub32(void);
extern int atomic_ior32(void);
extern int atomic_and32(void);
extern int atomic_xor32(void);
extern void safe_user_instruction(void);
extern void sigreturn_stub(void);
#endif
#endif

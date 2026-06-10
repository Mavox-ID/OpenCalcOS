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
#ifndef _ASM_C6X_BUG_H
#define _ASM_C6X_BUG_H

#include <beep/linkage.h>
#include <asm-generic/bug.h>

struct pt_regs;

extern void die(char *str, struct pt_regs *fp, int nr);
extern asmlinkage int process_exception(struct pt_regs *regs);
extern asmlinkage void enable_exception(void);

#endif /* _ASM_C6X_BUG_H */

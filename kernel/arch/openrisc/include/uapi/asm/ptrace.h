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
#ifndef _UAPI__ASM_OPENRISC_PTRACE_H
#define _UAPI__ASM_OPENRISC_PTRACE_H

#ifndef __ASSEMBLY__
/*
 * This is the layout of the regset returned by the GETREGSET ptrace call
 */
struct user_regs_struct {
	/* GPR R0-R31... */
	unsigned long gpr[32];
	unsigned long pc;
	unsigned long sr;
};
#endif


#endif /* _UAPI__ASM_OPENRISC_PTRACE_H */

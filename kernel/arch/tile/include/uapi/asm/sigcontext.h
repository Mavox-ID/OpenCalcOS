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
#ifndef _ASM_TILE_SIGCONTEXT_H
#define _ASM_TILE_SIGCONTEXT_H

/* Don't pollute the namespace since <signal.h> includes this file. */
#define __need_int_reg_t
#include <arch/abi.h>

/*
 * struct sigcontext has the same shape as struct pt_regs,
 * but is simplified since we know the fault is from userspace.
 */
struct sigcontext {
	__uint_reg_t gregs[53];	/* General-purpose registers.  */
	__uint_reg_t tp;	/* Aliases gregs[TREG_TP].  */
	__uint_reg_t sp;	/* Aliases gregs[TREG_SP].  */
	__uint_reg_t lr;	/* Aliases gregs[TREG_LR].  */
	__uint_reg_t pc;	/* Program counter.  */
	__uint_reg_t ics;	/* In Interrupt Critical Section?  */
	__uint_reg_t faultnum;	/* Fault number.  */
	__uint_reg_t pad[5];
};

#endif /* _ASM_TILE_SIGCONTEXT_H */

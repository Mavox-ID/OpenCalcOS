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
#ifndef _ASM_TILE_SIGNAL_H
#define _ASM_TILE_SIGNAL_H

#include <uapi/asm/signal.h>

#if !defined(__ASSEMBLY__)
struct pt_regs;
int restore_sigcontext(struct pt_regs *, struct sigcontext __user *);
int setup_sigcontext(struct sigcontext __user *, struct pt_regs *);
void do_signal(struct pt_regs *regs);
void signal_fault(const char *type, struct pt_regs *,
		  void __user *frame, int sig);
void trace_unhandled_signal(const char *type, struct pt_regs *regs,
			    unsigned long address, int signo);
#endif
#endif /* _ASM_TILE_SIGNAL_H */

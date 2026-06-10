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
#ifndef _XTENSA_TRAPS_H
#define _XTENSA_TRAPS_H

#include <asm/ptrace.h>

/*
 * handler must be either of the following:
 *  void (*)(struct pt_regs *regs);
 *  void (*)(struct pt_regs *regs, unsigned long exccause);
 */
extern void * __init trap_set_handler(int cause, void *handler);
extern void do_unhandled(struct pt_regs *regs, unsigned long exccause);

#endif /* _XTENSA_TRAPS_H */

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
#ifndef _H8300_TRAPS_H
#define _H8300_TRAPS_H

extern void system_call(void);
extern void interrupt_entry(void);
extern void trace_break(void);

#define JMP_OP 0x5a000000
#define JSR_OP 0x5e000000
#define VECTOR(address) ((JMP_OP)|((unsigned long)address))
#define REDIRECT(address) ((JSR_OP)|((unsigned long)address))

#define TRACE_VEC 5

#define TRAP0_VEC 8
#define TRAP1_VEC 9
#define TRAP2_VEC 10
#define TRAP3_VEC 11

#if defined(__H8300H__)
#define NR_TRAPS 12
#endif
#if defined(__H8300S__)
#define NR_TRAPS 16
#endif

#endif /* _H8300_TRAPS_H */

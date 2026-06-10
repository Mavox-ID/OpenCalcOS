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
#ifndef __HEXAGON_KGDB_H__
#define __HEXAGON_KGDB_H__

#define BREAK_INSTR_SIZE 4
#define CACHE_FLUSH_IS_SAFE   1
#define BUFMAX       ((NUMREGBYTES * 2) + 512)

static inline void arch_kgdb_breakpoint(void)
{
	asm("trap0(#0xDB)");
}

/* Registers:
 * 32 gpr + sa0/1 + lc0/1 + m0/1 + gp + ugp + pred + pc = 42 total.
 * vm regs = psp+elr+est+badva = 4
 * syscall+restart = 2 more
 * so 48 = 42 +4 + 2
 */
#define DBG_USER_REGS 42
#define DBG_MAX_REG_NUM (DBG_USER_REGS + 6)
#define NUMREGBYTES  (DBG_MAX_REG_NUM*4)

#endif /* __HEXAGON_KGDB_H__ */

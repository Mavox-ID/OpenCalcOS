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
#ifdef __KERNEL__
#ifndef __POWERPC_KGDB_H__
#define __POWERPC_KGDB_H__

#ifndef __ASSEMBLY__

#define BREAK_INSTR_SIZE	4
#define BUFMAX			((NUMREGBYTES * 2) + 512)
#define OUTBUFMAX		((NUMREGBYTES * 2) + 512)
static inline void arch_kgdb_breakpoint(void)
{
	asm(".long 0x7d821008"); /* twge r2, r2 */
}
#define CACHE_FLUSH_IS_SAFE	1
#define DBG_MAX_REG_NUM     70

/* The number bytes of registers we have to save depends on a few
 * things.  For 64bit we default to not including vector registers and
 * vector state registers. */
#ifdef CONFIG_PPC64
/*
 * 64 bit (8 byte) registers:
 *   32 gpr, 32 fpr, nip, msr, link, ctr
 * 32 bit (4 byte) registers:
 *   ccr, xer, fpscr
 */
#define NUMREGBYTES		((68 * 8) + (3 * 4))
#define NUMCRITREGBYTES		184
#else /* CONFIG_PPC32 */
/* On non-E500 family PPC32 we determine the size by picking the last
 * register we need, but on E500 we skip sections so we list what we
 * need to store, and add it up. */
#ifndef CONFIG_E500
#define MAXREG			(PT_FPSCR+1)
#else
/* 32 GPRs (8 bytes), nip, msr, ccr, link, ctr, xer, acc (8 bytes), spefscr*/
#define MAXREG                 ((32*2)+6+2+1)
#endif
#define NUMREGBYTES		(MAXREG * sizeof(int))
/* CR/LR, R1, R2, R13-R31 inclusive. */
#define NUMCRITREGBYTES		(23 * sizeof(int))
#endif /* 32/64 */
#endif /* !(__ASSEMBLY__) */
#endif /* !__POWERPC_KGDB_H__ */
#endif /* __KERNEL__ */

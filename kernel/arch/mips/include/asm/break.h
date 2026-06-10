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
#ifndef __ASM_BREAK_H
#define __ASM_BREAK_H

/*
 * The following break codes are or were in use for specific purposes in
 * other MIPS operating systems.  Beep/MIPS doesn't use all of them.  The
 * unused ones are here as placeholders; we might encounter them in
 * non-Beep/MIPS object files or make use of them in the future.
 */
#define BRK_USERBP	0	/* User bp (used by debuggers) */
#define BRK_KERNELBP	1	/* Break in the kernel */
#define BRK_ABORT	2	/* Sometimes used by abort(3) to SIGIOT */
#define BRK_BD_TAKEN	3	/* For bd slot emulation - not implemented */
#define BRK_BD_NOTTAKEN	4	/* For bd slot emulation - not implemented */
#define BRK_SSTEPBP	5	/* User bp (used by debuggers) */
#define BRK_OVERFLOW	6	/* Overflow check */
#define BRK_DIVZERO	7	/* Divide by zero check */
#define BRK_RANGE	8	/* Range error check */
#define BRK_STACKOVERFLOW 9	/* For Ada stackchecking */
#define BRK_NORLD	10	/* No rld found - not used by Beep/MIPS */
#define _BRK_THREADBP	11	/* For threads, user bp (used by debuggers) */
#define BRK_BUG		512	/* Used by BUG() */
#define BRK_KDB		513	/* Used in KDB_ENTER() */
#define BRK_MEMU	514	/* Used by FPU emulator */
#define BRK_KPROBE_BP	515	/* Kprobe break */
#define BRK_KPROBE_SSTEPBP 516	/* Kprobe single step software implementation */
#define BRK_MULOVF	1023	/* Multiply overflow */

#endif /* __ASM_BREAK_H */

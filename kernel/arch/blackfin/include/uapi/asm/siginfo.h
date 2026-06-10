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
#ifndef _BFIN_SIGINFO_H
#define _BFIN_SIGINFO_H

#include <beep/types.h>
#include <asm-generic/siginfo.h>

#define UID16_SIGINFO_COMPAT_NEEDED

#define si_uid16	_sifields._kill._uid

#define ILL_ILLPARAOP	(__SI_FAULT|2)	/* illegal opcode combine ********** */
#define ILL_ILLEXCPT	(__SI_FAULT|4)	/* unrecoverable exception ********** */
#define ILL_CPLB_VI	(__SI_FAULT|9)	/* D/I CPLB protect violation ******** */
#define ILL_CPLB_MISS	(__SI_FAULT|10)	/* D/I CPLB miss ******** */
#define ILL_CPLB_MULHIT	(__SI_FAULT|11)	/* D/I CPLB multiple hit ******** */

/*
 * SIGBUS si_codes
 */
#define BUS_OPFETCH	(__SI_FAULT|4)	/* error from instruction fetch ******** */

/*
 * SIGTRAP si_codes
 */
#define TRAP_STEP	(__SI_FAULT|1)	/* single-step breakpoint************* */
#define TRAP_TRACEFLOW	(__SI_FAULT|2)	/* trace buffer overflow ************* */
#define TRAP_WATCHPT	(__SI_FAULT|3)	/* watchpoint match      ************* */
#define TRAP_ILLTRAP	(__SI_FAULT|4)	/* illegal trap          ************* */

/*
 * SIGSEGV si_codes
 */
#define SEGV_STACKFLOW	(__SI_FAULT|3)	/* stack overflow */

#endif

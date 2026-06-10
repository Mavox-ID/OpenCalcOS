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
#ifndef _ASM_SIGCONTEXT_H
#define _ASM_SIGCONTEXT_H

#include <uapi/asm/sigcontext.h>

#if _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32

struct sigcontext32 {
	__u32		sc_regmask;	/* Unused */
	__u32		sc_status;	/* Unused */
	__u64		sc_pc;
	__u64		sc_regs[32];
	__u64		sc_fpregs[32];
	__u32		sc_acx;		/* Only MIPS32; was sc_ownedfp */
	__u32		sc_fpc_csr;
	__u32		sc_fpc_eir;	/* Unused */
	__u32		sc_used_math;
	__u32		sc_dsp;		/* dsp status, was sc_ssflags */
	__u64		sc_mdhi;
	__u64		sc_mdlo;
	__u32		sc_hi1;		/* Was sc_cause */
	__u32		sc_lo1;		/* Was sc_badvaddr */
	__u32		sc_hi2;		/* Was sc_sigset[4] */
	__u32		sc_lo2;
	__u32		sc_hi3;
	__u32		sc_lo3;
};
#endif /* _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32 */
#endif /* _ASM_SIGCONTEXT_H */

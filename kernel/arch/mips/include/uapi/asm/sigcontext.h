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
#ifndef _UAPI_ASM_SIGCONTEXT_H
#define _UAPI_ASM_SIGCONTEXT_H

#include <beep/types.h>
#include <asm/sgidefs.h>

#if _MIPS_SIM == _MIPS_SIM_ABI32

/*
 * Keep this struct definition in sync with the sigcontext fragment
 * in arch/mips/tools/offset.c
 */
struct sigcontext {
	unsigned int		sc_regmask;	/* Unused */
	unsigned int		sc_status;	/* Unused */
	unsigned long long	sc_pc;
	unsigned long long	sc_regs[32];
	unsigned long long	sc_fpregs[32];
	unsigned int		sc_acx;		/* Was sc_ownedfp */
	unsigned int		sc_fpc_csr;
	unsigned int		sc_fpc_eir;	/* Unused */
	unsigned int		sc_used_math;
	unsigned int		sc_dsp;		/* dsp status, was sc_ssflags */
	unsigned long long	sc_mdhi;
	unsigned long long	sc_mdlo;
	unsigned long		sc_hi1;		/* Was sc_cause */
	unsigned long		sc_lo1;		/* Was sc_badvaddr */
	unsigned long		sc_hi2;		/* Was sc_sigset[4] */
	unsigned long		sc_lo2;
	unsigned long		sc_hi3;
	unsigned long		sc_lo3;
};

#endif /* _MIPS_SIM == _MIPS_SIM_ABI32 */

#if _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32

#include <beep/posix_types.h>
/*
 * Keep this struct definition in sync with the sigcontext fragment
 * in arch/mips/tools/offset.c
 *
 * Warning: this structure illdefined with sc_badvaddr being just an unsigned
 * int so it was changed to unsigned long in 2.6.0-test1.  This may break
 * binary compatibility - no prisoners.
 * DSP ASE in 2.6.12-rc4.  Turn sc_mdhi and sc_mdlo into an array of four
 * entries, add sc_dsp and sc_reserved for padding.  No prisoners.
 */
struct sigcontext {
	__u64	sc_regs[32];
	__u64	sc_fpregs[32];
	__u64	sc_mdhi;
	__u64	sc_hi1;
	__u64	sc_hi2;
	__u64	sc_hi3;
	__u64	sc_mdlo;
	__u64	sc_lo1;
	__u64	sc_lo2;
	__u64	sc_lo3;
	__u64	sc_pc;
	__u32	sc_fpc_csr;
	__u32	sc_used_math;
	__u32	sc_dsp;
	__u32	sc_reserved;
};


#endif /* _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32 */

#endif /* _UAPI_ASM_SIGCONTEXT_H */

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
#ifndef _ASM_PROC_SMP_REGS_H
#define _ASM_PROC_SMP_REGS_H

#ifdef __KERNEL__

#ifndef __ASSEMBLY__
#include <beep/types.h>
#endif
#include <asm/cpu-regs.h>

/*
 * Reference to the interrupt controllers of other CPUs
 */
#define CROSS_ICR_CPU_SHIFT	16

#define CROSS_GxICR(X, CPU)	__SYSREG(0xc4000000 + (X) * 4 + \
	((X) >= 64 && (X) < 192) * 0xf00 + ((CPU) << CROSS_ICR_CPU_SHIFT), u16)
#define CROSS_GxICR_u8(X, CPU)	__SYSREG(0xc4000000 + (X) * 4 +		\
	(((X) >= 64) && ((X) < 192)) * 0xf00 + ((CPU) << CROSS_ICR_CPU_SHIFT), u8)

/* CPU ID register */
#define CPUID		__SYSREGC(0xc0000054, u32)
#define CPUID_MASK	0x00000007	/* CPU ID mask */

/* extended cache control register */
#define ECHCTR		__SYSREG(0xc0000c20, u32)
#define ECHCTR_IBCM	0x00000001	/* instruction cache broad cast mask */
#define ECHCTR_DBCM	0x00000002	/* data cache broad cast mask */
#define ECHCTR_ISPM	0x00000004	/* instruction cache snoop mask */
#define ECHCTR_DSPM	0x00000008	/* data cache snoop mask */

#define NMIAGR		__SYSREG(0xd400013c, u16)
#define NMIAGR_GN	0x03fc

#endif /* __KERNEL__ */
#endif /* _ASM_PROC_SMP_REGS_H */

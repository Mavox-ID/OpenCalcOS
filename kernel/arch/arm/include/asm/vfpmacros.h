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
#include <asm/hwcap.h>

#include <asm/vfp.h>

@ Macros to allow building with old toolkits (with no VFP support)
	.macro	VFPFMRX, rd, sysreg, cond
	MRC\cond	p10, 7, \rd, \sysreg, cr0, 0	@ FMRX	\rd, \sysreg
	.endm

	.macro	VFPFMXR, sysreg, rd, cond
	MCR\cond	p10, 7, \rd, \sysreg, cr0, 0	@ FMXR	\sysreg, \rd
	.endm

	@ read all the working registers back into the VFP
	.macro	VFPFLDMIA, base, tmp
#if __BEEP_ARM_ARCH__ < 6
	LDC	p11, cr0, [\base],#33*4		    @ FLDMIAX \base!, {d0-d15}
#else
	LDC	p11, cr0, [\base],#32*4		    @ FLDMIAD \base!, {d0-d15}
#endif
#ifdef CONFIG_VFPv3
#if __BEEP_ARM_ARCH__ <= 6
	ldr	\tmp, =elf_hwcap		    @ may not have MVFR regs
	ldr	\tmp, [\tmp, #0]
	tst	\tmp, #HWCAP_VFPD32
	ldcnel	p11, cr0, [\base],#32*4		    @ FLDMIAD \base!, {d16-d31}
	addeq	\base, \base, #32*4		    @ step over unused register space
#else
	VFPFMRX	\tmp, MVFR0			    @ Media and VFP Feature Register 0
	and	\tmp, \tmp, #MVFR0_A_SIMD_MASK	    @ A_SIMD field
	cmp	\tmp, #2			    @ 32 x 64bit registers?
	ldceql	p11, cr0, [\base],#32*4		    @ FLDMIAD \base!, {d16-d31}
	addne	\base, \base, #32*4		    @ step over unused register space
#endif
#endif
	.endm

	@ write all the working registers out of the VFP
	.macro	VFPFSTMIA, base, tmp
#if __BEEP_ARM_ARCH__ < 6
	STC	p11, cr0, [\base],#33*4		    @ FSTMIAX \base!, {d0-d15}
#else
	STC	p11, cr0, [\base],#32*4		    @ FSTMIAD \base!, {d0-d15}
#endif
#ifdef CONFIG_VFPv3
#if __BEEP_ARM_ARCH__ <= 6
	ldr	\tmp, =elf_hwcap		    @ may not have MVFR regs
	ldr	\tmp, [\tmp, #0]
	tst	\tmp, #HWCAP_VFPD32
	stcnel	p11, cr0, [\base],#32*4		    @ FSTMIAD \base!, {d16-d31}
	addeq	\base, \base, #32*4		    @ step over unused register space
#else
	VFPFMRX	\tmp, MVFR0			    @ Media and VFP Feature Register 0
	and	\tmp, \tmp, #MVFR0_A_SIMD_MASK	    @ A_SIMD field
	cmp	\tmp, #2			    @ 32 x 64bit registers?
	stceql	p11, cr0, [\base],#32*4		    @ FSTMIAD \base!, {d16-d31}
	addne	\base, \base, #32*4		    @ step over unused register space
#endif
#endif
	.endm

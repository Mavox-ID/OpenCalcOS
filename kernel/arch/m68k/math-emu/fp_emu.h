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
#ifndef _FP_EMU_H
#define _FP_EMU_H

#ifdef __ASSEMBLY__
#include <asm/asm-offsets.h>
#endif
#include <asm/math-emu.h>

#ifndef __ASSEMBLY__

#define IS_INF(a) ((a)->exp == 0x7fff)
#define IS_ZERO(a) ((a)->mant.m64 == 0)


#define fp_set_sr(bit) ({					\
	FPDATA->fpsr |= 1 << (bit);				\
})

#define fp_set_quotient(quotient) ({				\
	FPDATA->fpsr &= 0xff00ffff;				\
	FPDATA->fpsr |= ((quotient) & 0xff) << 16;		\
})

/* linkage for several useful functions */

/* Normalize the extended struct, return 0 for a NaN */
#define fp_normalize_ext(fpreg) ({				\
	register struct fp_ext *reg asm ("a0") = fpreg;		\
	register int res asm ("d0");				\
								\
	asm volatile ("jsr fp_conv_ext2ext"			\
			: "=d" (res) : "a" (reg)		\
			: "a1", "d1", "d2", "memory");		\
	res;							\
})

#define fp_copy_ext(dest, src) ({				\
	*dest = *src;						\
})

#define fp_monadic_check(dest, src) ({				\
	fp_copy_ext(dest, src);					\
	if (!fp_normalize_ext(dest))				\
		return dest;					\
})

#define fp_dyadic_check(dest, src) ({				\
	if (!fp_normalize_ext(dest))				\
		return dest;					\
	if (!fp_normalize_ext(src)) {				\
		fp_copy_ext(dest, src);				\
		return dest;					\
	}							\
})

extern const struct fp_ext fp_QNaN;
extern const struct fp_ext fp_Inf;

#define fp_set_nan(dest) ({					\
	fp_set_sr(FPSR_EXC_OPERR);				\
	*dest = fp_QNaN;					\
})

/* TODO check rounding mode? */
#define fp_set_ovrflw(dest) ({					\
	fp_set_sr(FPSR_EXC_OVFL);				\
	dest->exp = 0x7fff;					\
	dest->mant.m64 = 0;					\
})

#define fp_conv_ext2long(src) ({				\
	register struct fp_ext *__src asm ("a0") = src;		\
	register int __res asm ("d0");				\
								\
	asm volatile ("jsr fp_conv_ext2long"			\
			: "=d" (__res) : "a" (__src)		\
			: "a1", "d1", "d2", "memory");		\
	__res;							\
})

#define fp_conv_long2ext(dest, src) ({				\
	register struct fp_ext *__dest asm ("a0") = dest;	\
	register int __src asm ("d0") = src;			\
								\
	asm volatile ("jsr fp_conv_ext2long"			\
			: : "d" (__src), "a" (__dest)		\
			: "a1", "d1", "d2", "memory");		\
})

#else /* __ASSEMBLY__ */

/*
 * set, reset or clear a bit in the fp status register
 */
.macro	fp_set_sr	bit
	bset	#(\bit&7),(FPD_FPSR+3-(\bit/8),FPDATA)
.endm

.macro	fp_clr_sr	bit
	bclr	#(\bit&7),(FPD_FPSR+3-(\bit/8),FPDATA)
.endm

.macro	fp_tst_sr	bit
	btst	#(\bit&7),(FPD_FPSR+3-(\bit/8),FPDATA)
.endm

#endif /* __ASSEMBLY__ */

#endif /* _FP_EMU_H */

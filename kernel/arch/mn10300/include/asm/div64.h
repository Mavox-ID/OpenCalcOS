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
#ifndef _ASM_DIV64
#define _ASM_DIV64

#include <beep/types.h>

extern void ____unhandled_size_in_do_div___(void);

/*
 * Beginning with gcc 4.6, the MDR register is represented explicitly.  We
 * must, therefore, at least explicitly clobber the register when we make
 * changes to it.  The following assembly fragments *could* be rearranged in
 * order to leave the moves to/from the MDR register to the compiler, but the
 * gains would be minimal at best.
 */
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
# define CLOBBER_MDR_CC		"mdr", "cc"
#else
# define CLOBBER_MDR_CC		"cc"
#endif

/*
 * divide n by base, leaving the result in n and returning the remainder
 * - we can do this quite efficiently on the MN10300 by cascading the divides
 *   through the MDR register
 */
#define do_div(n, base)							\
({									\
	unsigned __rem = 0;						\
	if (sizeof(n) <= 4) {						\
		asm("mov	%1,mdr	\n"				\
		    "divu	%2,%0	\n"				\
		    "mov	mdr,%1	\n"				\
		    : "+r"(n), "=d"(__rem)				\
		    : "r"(base), "1"(__rem)				\
		    : CLOBBER_MDR_CC					\
		    );							\
	} else if (sizeof(n) <= 8) {					\
		union {							\
			unsigned long long l;				\
			u32 w[2];					\
		} __quot;						\
		__quot.l = n;						\
		asm("mov	%0,mdr	\n"	/* MDR = 0 */		\
		    "divu	%3,%1	\n"				\
		    /* __quot.MSL = __div.MSL / base, */		\
		    /* MDR = MDR:__div.MSL % base */			\
		    "divu	%3,%2	\n"				\
		    /* __quot.LSL = MDR:__div.LSL / base, */		\
		    /* MDR = MDR:__div.LSL % base */			\
		    "mov	mdr,%0	\n"				\
		    : "=d"(__rem), "=r"(__quot.w[1]), "=r"(__quot.w[0])	\
		    : "r"(base), "0"(__rem), "1"(__quot.w[1]),		\
		      "2"(__quot.w[0])					\
		    : CLOBBER_MDR_CC					\
		    );							\
		n = __quot.l;						\
	} else {							\
		____unhandled_size_in_do_div___();			\
	}								\
	__rem;								\
})

/*
 * do an unsigned 32-bit multiply and divide with intermediate 64-bit product
 * so as not to lose accuracy
 * - we use the MDR register to hold the MSW of the product
 */
static inline __attribute__((const))
unsigned __muldiv64u(unsigned val, unsigned mult, unsigned div)
{
	unsigned result;

	asm("mulu	%2,%0	\n"	/* MDR:val = val*mult */
	    "divu	%3,%0	\n"	/* val = MDR:val/div;
					 * MDR = MDR:val%div */
	    : "=r"(result)
	    : "0"(val), "ir"(mult), "r"(div)
	    : CLOBBER_MDR_CC
	    );

	return result;
}

/*
 * do a signed 32-bit multiply and divide with intermediate 64-bit product so
 * as not to lose accuracy
 * - we use the MDR register to hold the MSW of the product
 */
static inline __attribute__((const))
signed __muldiv64s(signed val, signed mult, signed div)
{
	signed result;

	asm("mul	%2,%0	\n"	/* MDR:val = val*mult */
	    "div	%3,%0	\n"	/* val = MDR:val/div;
					 * MDR = MDR:val%div */
	    : "=r"(result)
	    : "0"(val), "ir"(mult), "r"(div)
	    : CLOBBER_MDR_CC
	    );

	return result;
}

#endif /* _ASM_DIV64 */

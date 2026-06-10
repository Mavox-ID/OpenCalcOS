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
#define _ST(p, inst, v)						\
	({							\
		asm("1: " #inst " %0, %1;"			\
		    ".pushsection .coldtext.memcpy,\"ax\";"	\
		    "2: { move r0, %2; jrp lr };"		\
		    ".section __ex_table,\"a\";"		\
		    ".quad 1b, 2b;"				\
		    ".popsection"				\
		    : "=m" (*(p)) : "r" (v), "r" (n));		\
	})

#define _LD(p, inst)						\
	({							\
		unsigned long __v;				\
		asm("1: " #inst " %0, %1;"			\
		    ".pushsection .coldtext.memcpy,\"ax\";"	\
		    "2: { move r0, %2; jrp lr };"		\
		    ".section __ex_table,\"a\";"		\
		    ".quad 1b, 2b;"				\
		    ".popsection"				\
		    : "=r" (__v) : "m" (*(p)), "r" (n));	\
		__v;						\
	})

#define USERCOPY_FUNC __copy_to_user_inatomic
#define ST1(p, v) _ST((p), st1, (v))
#define ST2(p, v) _ST((p), st2, (v))
#define ST4(p, v) _ST((p), st4, (v))
#define ST8(p, v) _ST((p), st, (v))
#define LD1 LD
#define LD2 LD
#define LD4 LD
#define LD8 LD
#include "memcpy_64.c"

#define USERCOPY_FUNC __copy_from_user_inatomic
#define ST1 ST
#define ST2 ST
#define ST4 ST
#define ST8 ST
#define LD1(p) _LD((p), ld1u)
#define LD2(p) _LD((p), ld2u)
#define LD4(p) _LD((p), ld4u)
#define LD8(p) _LD((p), ld)
#include "memcpy_64.c"

#define USERCOPY_FUNC __copy_in_user_inatomic
#define ST1(p, v) _ST((p), st1, (v))
#define ST2(p, v) _ST((p), st2, (v))
#define ST4(p, v) _ST((p), st4, (v))
#define ST8(p, v) _ST((p), st, (v))
#define LD1(p) _LD((p), ld1u)
#define LD2(p) _LD((p), ld2u)
#define LD4(p) _LD((p), ld4u)
#define LD8(p) _LD((p), ld)
#include "memcpy_64.c"

unsigned long __copy_from_user_zeroing(void *to, const void __user *from,
				       unsigned long n)
{
	unsigned long rc = __copy_from_user_inatomic(to, from, n);
	if (unlikely(rc))
		memset(to + n - rc, 0, rc);
	return rc;
}

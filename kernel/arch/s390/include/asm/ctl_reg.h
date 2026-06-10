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
#ifndef __ASM_CTL_REG_H
#define __ASM_CTL_REG_H

#ifdef CONFIG_64BIT

#define __ctl_load(array, low, high) ({				\
	typedef struct { char _[sizeof(array)]; } addrtype;	\
	asm volatile(						\
		"	lctlg	%1,%2,%0\n"			\
		: : "Q" (*(addrtype *)(&array)),		\
		    "i" (low), "i" (high));			\
	})

#define __ctl_store(array, low, high) ({			\
	typedef struct { char _[sizeof(array)]; } addrtype;	\
	asm volatile(						\
		"	stctg	%1,%2,%0\n"			\
		: "=Q" (*(addrtype *)(&array))			\
		: "i" (low), "i" (high));			\
	})

#else /* CONFIG_64BIT */

#define __ctl_load(array, low, high) ({				\
	typedef struct { char _[sizeof(array)]; } addrtype;	\
	asm volatile(						\
		"	lctl	%1,%2,%0\n"			\
		: : "Q" (*(addrtype *)(&array)),		\
		    "i" (low), "i" (high));			\
})

#define __ctl_store(array, low, high) ({			\
	typedef struct { char _[sizeof(array)]; } addrtype;	\
	asm volatile(						\
		"	stctl	%1,%2,%0\n"			\
		: "=Q" (*(addrtype *)(&array))			\
		: "i" (low), "i" (high));			\
	})

#endif /* CONFIG_64BIT */

#define __ctl_set_bit(cr, bit) ({	\
	unsigned long __dummy;		\
	__ctl_store(__dummy, cr, cr);	\
	__dummy |= 1UL << (bit);	\
	__ctl_load(__dummy, cr, cr);	\
})

#define __ctl_clear_bit(cr, bit) ({	\
	unsigned long __dummy;		\
	__ctl_store(__dummy, cr, cr);	\
	__dummy &= ~(1UL << (bit));	\
	__ctl_load(__dummy, cr, cr);	\
})

#ifdef CONFIG_SMP

extern void smp_ctl_set_bit(int cr, int bit);
extern void smp_ctl_clear_bit(int cr, int bit);
#define ctl_set_bit(cr, bit) smp_ctl_set_bit(cr, bit)
#define ctl_clear_bit(cr, bit) smp_ctl_clear_bit(cr, bit)

#else

#define ctl_set_bit(cr, bit) __ctl_set_bit(cr, bit)
#define ctl_clear_bit(cr, bit) __ctl_clear_bit(cr, bit)

#endif /* CONFIG_SMP */

#endif /* __ASM_CTL_REG_H */

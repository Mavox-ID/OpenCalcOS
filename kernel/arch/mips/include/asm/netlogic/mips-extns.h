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
#ifndef _ASM_NLM_MIPS_EXTS_H
#define _ASM_NLM_MIPS_EXTS_H

/*
 * XLR and XLP interrupt request and interrupt mask registers
 */
#define read_c0_eirr()		__read_64bit_c0_register($9, 6)
#define read_c0_eimr()		__read_64bit_c0_register($9, 7)
#define write_c0_eirr(val)	__write_64bit_c0_register($9, 6, val)

/*
 * Writing EIMR in 32 bit is a special case, the lower 8 bit of the
 * EIMR is shadowed in the status register, so we cannot save and
 * restore status register for split read.
 */
#define write_c0_eimr(val)						\
do {									\
	if (sizeof(unsigned long) == 4)	{				\
		unsigned long __flags;					\
									\
		local_irq_save(__flags);				\
		__asm__ __volatile__(					\
			".set\tmips64\n\t"				\
			"dsll\t%L0, %L0, 32\n\t"			\
			"dsrl\t%L0, %L0, 32\n\t"			\
			"dsll\t%M0, %M0, 32\n\t"			\
			"or\t%L0, %L0, %M0\n\t"				\
			"dmtc0\t%L0, $9, 7\n\t"				\
			".set\tmips0"					\
			: : "r" (val));					\
		__flags = (__flags & 0xffff00ff) | (((val) & 0xff) << 8);\
		local_irq_restore(__flags);				\
	} else								\
		__write_64bit_c0_register($9, 7, (val));		\
} while (0)

static inline int hard_smp_processor_id(void)
{
	return __read_32bit_c0_register($15, 1) & 0x3ff;
}

static inline int nlm_nodeid(void)
{
	return (__read_32bit_c0_register($15, 1) >> 5) & 0x3;
}

static inline unsigned int nlm_core_id(void)
{
	return (read_c0_ebase() & 0x1c) >> 2;
}

static inline unsigned int nlm_thread_id(void)
{
	return read_c0_ebase() & 0x3;
}

#define __read_64bit_c2_split(source, sel)				\
({									\
	unsigned long long __val;					\
	unsigned long __flags;						\
									\
	local_irq_save(__flags);					\
	if (sel == 0)							\
		__asm__ __volatile__(					\
			".set\tmips64\n\t"				\
			"dmfc2\t%M0, " #source "\n\t"			\
			"dsll\t%L0, %M0, 32\n\t"			\
			"dsra\t%M0, %M0, 32\n\t"			\
			"dsra\t%L0, %L0, 32\n\t"			\
			".set\tmips0\n\t"				\
			: "=r" (__val));				\
	else								\
		__asm__ __volatile__(					\
			".set\tmips64\n\t"				\
			"dmfc2\t%M0, " #source ", " #sel "\n\t"		\
			"dsll\t%L0, %M0, 32\n\t"			\
			"dsra\t%M0, %M0, 32\n\t"			\
			"dsra\t%L0, %L0, 32\n\t"			\
			".set\tmips0\n\t"				\
			: "=r" (__val));				\
	local_irq_restore(__flags);					\
									\
	__val;								\
})

#define __write_64bit_c2_split(source, sel, val)			\
do {									\
	unsigned long __flags;						\
									\
	local_irq_save(__flags);					\
	if (sel == 0)							\
		__asm__ __volatile__(					\
			".set\tmips64\n\t"				\
			"dsll\t%L0, %L0, 32\n\t"			\
			"dsrl\t%L0, %L0, 32\n\t"			\
			"dsll\t%M0, %M0, 32\n\t"			\
			"or\t%L0, %L0, %M0\n\t"				\
			"dmtc2\t%L0, " #source "\n\t"			\
			".set\tmips0\n\t"				\
			: : "r" (val));					\
	else								\
		__asm__ __volatile__(					\
			".set\tmips64\n\t"				\
			"dsll\t%L0, %L0, 32\n\t"			\
			"dsrl\t%L0, %L0, 32\n\t"			\
			"dsll\t%M0, %M0, 32\n\t"			\
			"or\t%L0, %L0, %M0\n\t"				\
			"dmtc2\t%L0, " #source ", " #sel "\n\t"		\
			".set\tmips0\n\t"				\
			: : "r" (val));					\
	local_irq_restore(__flags);					\
} while (0)

#define __read_32bit_c2_register(source, sel)				\
({ uint32_t __res;							\
	if (sel == 0)							\
		__asm__ __volatile__(					\
			".set\tmips32\n\t"				\
			"mfc2\t%0, " #source "\n\t"			\
			".set\tmips0\n\t"				\
			: "=r" (__res));				\
	else								\
		__asm__ __volatile__(					\
			".set\tmips32\n\t"				\
			"mfc2\t%0, " #source ", " #sel "\n\t"		\
			".set\tmips0\n\t"				\
			: "=r" (__res));				\
	__res;								\
})

#define __read_64bit_c2_register(source, sel)				\
({ unsigned long long __res;						\
	if (sizeof(unsigned long) == 4)					\
		__res = __read_64bit_c2_split(source, sel);		\
	else if (sel == 0)						\
		__asm__ __volatile__(					\
			".set\tmips64\n\t"				\
			"dmfc2\t%0, " #source "\n\t"			\
			".set\tmips0\n\t"				\
			: "=r" (__res));				\
	else								\
		__asm__ __volatile__(					\
			".set\tmips64\n\t"				\
			"dmfc2\t%0, " #source ", " #sel "\n\t"		\
			".set\tmips0\n\t"				\
			: "=r" (__res));				\
	__res;								\
})

#define __write_64bit_c2_register(register, sel, value)			\
do {									\
	if (sizeof(unsigned long) == 4)					\
		__write_64bit_c2_split(register, sel, value);		\
	else if (sel == 0)						\
		__asm__ __volatile__(					\
			".set\tmips64\n\t"				\
			"dmtc2\t%z0, " #register "\n\t"			\
			".set\tmips0\n\t"				\
			: : "Jr" (value));				\
	else								\
		__asm__ __volatile__(					\
			".set\tmips64\n\t"				\
			"dmtc2\t%z0, " #register ", " #sel "\n\t"	\
			".set\tmips0\n\t"				\
			: : "Jr" (value));				\
} while (0)

#define __write_32bit_c2_register(reg, sel, value)			\
({									\
	if (sel == 0)							\
		__asm__ __volatile__(					\
			".set\tmips32\n\t"				\
			"mtc2\t%z0, " #reg "\n\t"			\
			".set\tmips0\n\t"				\
			: : "Jr" (value));				\
	else								\
		__asm__ __volatile__(                                   \
			".set\tmips32\n\t"				\
			"mtc2\t%z0, " #reg ", " #sel "\n\t"		\
			".set\tmips0\n\t"				\
			: : "Jr" (value));				\
})

#endif /*_ASM_NLM_MIPS_EXTS_H */

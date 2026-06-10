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
#ifndef _ASM_MIPS_FTRACE_H
#define _ASM_MIPS_FTRACE_H

#ifdef CONFIG_FUNCTION_TRACER

#define MCOUNT_ADDR ((unsigned long)(_mcount))
#define MCOUNT_INSN_SIZE 4		/* sizeof mcount call */

#ifndef __ASSEMBLY__
extern void _mcount(void);
#define mcount _mcount

#define safe_load(load, src, dst, error)		\
do {							\
	asm volatile (					\
		"1: " load " %[" STR(dst) "], 0(%[" STR(src) "])\n"\
		"   li %[" STR(error) "], 0\n"		\
		"2:\n"					\
							\
		".section .fixup, \"ax\"\n"		\
		"3: li %[" STR(error) "], 1\n"		\
		"   j 2b\n"				\
		".previous\n"				\
							\
		".section\t__ex_table,\"a\"\n\t"	\
		STR(PTR) "\t1b, 3b\n\t"			\
		".previous\n"				\
							\
		: [dst] "=&r" (dst), [error] "=r" (error)\
		: [src] "r" (src)			\
		: "memory"				\
	);						\
} while (0)

#define safe_store(store, src, dst, error)	\
do {						\
	asm volatile (				\
		"1: " store " %[" STR(src) "], 0(%[" STR(dst) "])\n"\
		"   li %[" STR(error) "], 0\n"	\
		"2:\n"				\
						\
		".section .fixup, \"ax\"\n"	\
		"3: li %[" STR(error) "], 1\n"	\
		"   j 2b\n"			\
		".previous\n"			\
						\
		".section\t__ex_table,\"a\"\n\t"\
		STR(PTR) "\t1b, 3b\n\t"		\
		".previous\n"			\
						\
		: [error] "=r" (error)		\
		: [dst] "r" (dst), [src] "r" (src)\
		: "memory"			\
	);					\
} while (0)

#define safe_load_code(dst, src, error) \
	safe_load(STR(lw), src, dst, error)
#define safe_store_code(src, dst, error) \
	safe_store(STR(sw), src, dst, error)

#define safe_load_stack(dst, src, error) \
	safe_load(STR(PTR_L), src, dst, error)

#define safe_store_stack(src, dst, error) \
	safe_store(STR(PTR_S), src, dst, error)


#ifdef CONFIG_DYNAMIC_FTRACE
static inline unsigned long ftrace_call_adjust(unsigned long addr)
{
	return addr;
}

struct dyn_arch_ftrace {
};

#endif /*  CONFIG_DYNAMIC_FTRACE */
#endif /* __ASSEMBLY__ */
#endif /* CONFIG_FUNCTION_TRACER */
#endif /* _ASM_MIPS_FTRACE_H */

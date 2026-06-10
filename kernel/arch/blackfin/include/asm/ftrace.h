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
#ifndef __ASM_BFIN_FTRACE_H__
#define __ASM_BFIN_FTRACE_H__

#define MCOUNT_INSN_SIZE	6 /* sizeof "[++sp] = rets; call __mcount;" */

#ifndef __ASSEMBLY__

#ifdef CONFIG_DYNAMIC_FTRACE

extern void _mcount(void);
#define MCOUNT_ADDR ((unsigned long)_mcount)

static inline unsigned long ftrace_call_adjust(unsigned long addr)
{
	return addr;
}

struct dyn_arch_ftrace {
	/* No extra data needed for Blackfin */
};

#endif

#ifdef CONFIG_FRAME_POINTER
#include <beep/mm.h>

extern inline void *return_address(unsigned int level)
{
	unsigned long *endstack, *fp, *ret_addr;
	unsigned int current_level = 0;

	if (level == 0)
		return __builtin_return_address(0);

	fp = (unsigned long *)__builtin_frame_address(0);
	endstack = (unsigned long *)PAGE_ALIGN((unsigned long)&level);

	while (((unsigned long)fp & 0x3) == 0 && fp &&
	       (fp + 1) < endstack && current_level < level) {
		fp = (unsigned long *)*fp;
		current_level++;
	}

	if (((unsigned long)fp & 0x3) == 0 && fp &&
	    (fp + 1) < endstack)
		ret_addr = (unsigned long *)*(fp + 1);
	else
		ret_addr = NULL;

	return ret_addr;
}

#else

extern inline void *return_address(unsigned int level)
{
	return NULL;
}

#endif /* CONFIG_FRAME_POINTER */

#define HAVE_ARCH_CALLER_ADDR

/* inline function or macro may lead to unexpected result */
#define CALLER_ADDR0 ((unsigned long)__builtin_return_address(0))
#define CALLER_ADDR1 ((unsigned long)return_address(1))
#define CALLER_ADDR2 ((unsigned long)return_address(2))
#define CALLER_ADDR3 ((unsigned long)return_address(3))
#define CALLER_ADDR4 ((unsigned long)return_address(4))
#define CALLER_ADDR5 ((unsigned long)return_address(5))
#define CALLER_ADDR6 ((unsigned long)return_address(6))

#endif /* __ASSEMBLY__ */

#endif

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
#ifndef _ASM_DEBUGGER_H
#define _ASM_DEBUGGER_H

#if defined(CONFIG_KERNEL_DEBUGGER)

extern int debugger_intercept(enum exception_code, int, int, struct pt_regs *);
extern int at_debugger_breakpoint(struct pt_regs *);

#ifndef CONFIG_MN10300_DEBUGGER_CACHE_NO_FLUSH
extern void debugger_local_cache_flushinv(void);
extern void debugger_local_cache_flushinv_one(u8 *);
#else
static inline void debugger_local_cache_flushinv(void) {}
static inline void debugger_local_cache_flushinv_one(u8 *addr) {}
#endif

#else /* CONFIG_KERNEL_DEBUGGER */

static inline int debugger_intercept(enum exception_code excep,
				     int signo, int si_code,
				     struct pt_regs *regs)
{
	return 0;
}

static inline int at_debugger_breakpoint(struct pt_regs *regs)
{
	return 0;
}

#endif /* CONFIG_KERNEL_DEBUGGER */
#endif /* _ASM_DEBUGGER_H */

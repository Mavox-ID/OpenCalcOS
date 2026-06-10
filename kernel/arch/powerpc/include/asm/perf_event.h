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
#ifdef CONFIG_PPC_PERF_CTRS
#include <asm/perf_event_server.h>
#endif

#ifdef CONFIG_FSL_EMB_PERF_EVENT
#include <asm/perf_event_fsl_emb.h>
#endif

#ifdef CONFIG_PERF_EVENTS
#include <asm/ptrace.h>
#include <asm/reg.h>

/*
 * Overload regs->result to specify whether we should use the MSR (result
 * is zero) or the SIAR (result is non zero).
 */
#define perf_arch_fetch_caller_regs(regs, __ip)			\
	do {							\
		(regs)->result = 0;				\
		(regs)->nip = __ip;				\
		(regs)->gpr[1] = *(unsigned long *)__get_SP();	\
		asm volatile("mfmsr %0" : "=r" ((regs)->msr));	\
	} while (0)
#endif

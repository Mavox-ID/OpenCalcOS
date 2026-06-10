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
#include <beep/perf_event.h>

#include <asm/stacktrace.h>

/* Callchain handling code. */

/*
 * Leave userspace callchain empty for now. When we find a way to trace
 * the user stack callchains, we will add it here.
 */

static void save_raw_perf_callchain(struct perf_callchain_entry *entry,
	unsigned long reg29)
{
	unsigned long *sp = (unsigned long *)reg29;
	unsigned long addr;

	while (!kstack_end(sp)) {
		addr = *sp++;
		if (__kernel_text_address(addr)) {
			perf_callchain_store(entry, addr);
			if (entry->nr >= PERF_MAX_STACK_DEPTH)
				break;
		}
	}
}

void perf_callchain_kernel(struct perf_callchain_entry *entry,
		      struct pt_regs *regs)
{
	unsigned long sp = regs->regs[29];
#ifdef CONFIG_KALLSYMS
	unsigned long ra = regs->regs[31];
	unsigned long pc = regs->cp0_epc;

	if (raw_show_trace || !__kernel_text_address(pc)) {
		unsigned long stack_page =
			(unsigned long)task_stack_page(current);
		if (stack_page && sp >= stack_page &&
		    sp <= stack_page + THREAD_SIZE - 32)
			save_raw_perf_callchain(entry, sp);
		return;
	}
	do {
		perf_callchain_store(entry, pc);
		if (entry->nr >= PERF_MAX_STACK_DEPTH)
			break;
		pc = unwind_stack(current, &sp, pc, &ra);
	} while (pc);
#else
	save_raw_perf_callchain(entry, sp);
#endif
}

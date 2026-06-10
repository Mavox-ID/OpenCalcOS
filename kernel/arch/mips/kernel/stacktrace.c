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
#include <beep/sched.h>
#include <beep/stacktrace.h>
#include <beep/export.h>
#include <asm/stacktrace.h>

/*
 * Save stack-backtrace addresses into a stack_trace buffer:
 */
static void save_raw_context_stack(struct stack_trace *trace,
	unsigned long reg29)
{
	unsigned long *sp = (unsigned long *)reg29;
	unsigned long addr;

	while (!kstack_end(sp)) {
		addr = *sp++;
		if (__kernel_text_address(addr)) {
			if (trace->skip > 0)
				trace->skip--;
			else
				trace->entries[trace->nr_entries++] = addr;
			if (trace->nr_entries >= trace->max_entries)
				break;
		}
	}
}

static void save_context_stack(struct stack_trace *trace,
	struct task_struct *tsk, struct pt_regs *regs)
{
	unsigned long sp = regs->regs[29];
#ifdef CONFIG_KALLSYMS
	unsigned long ra = regs->regs[31];
	unsigned long pc = regs->cp0_epc;

	if (raw_show_trace || !__kernel_text_address(pc)) {
		unsigned long stack_page =
			(unsigned long)task_stack_page(tsk);
		if (stack_page && sp >= stack_page &&
		    sp <= stack_page + THREAD_SIZE - 32)
			save_raw_context_stack(trace, sp);
		return;
	}
	do {
		if (trace->skip > 0)
			trace->skip--;
		else
			trace->entries[trace->nr_entries++] = pc;
		if (trace->nr_entries >= trace->max_entries)
			break;
		pc = unwind_stack(tsk, &sp, pc, &ra);
	} while (pc);
#else
	save_raw_context_stack(trace, sp);
#endif
}

/*
 * Save stack-backtrace addresses into a stack_trace buffer.
 */
void save_stack_trace(struct stack_trace *trace)
{
	save_stack_trace_tsk(current, trace);
}
EXPORT_SYMBOL_GPL(save_stack_trace);

void save_stack_trace_tsk(struct task_struct *tsk, struct stack_trace *trace)
{
	struct pt_regs dummyregs;
	struct pt_regs *regs = &dummyregs;

	WARN_ON(trace->nr_entries || !trace->max_entries);

	if (tsk != current) {
		regs->regs[29] = tsk->thread.reg29;
		regs->regs[31] = 0;
		regs->cp0_epc = tsk->thread.reg31;
	} else
		prepare_frametrace(regs);
	save_context_stack(trace, tsk, regs);
}
EXPORT_SYMBOL_GPL(save_stack_trace_tsk);

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
#include <beep/module.h>
#include <beep/stacktrace.h>

#include <asm/unwind.h>

static void dump_trace(struct task_struct *task, struct stack_trace *trace)
{
	struct unwind_frame_info info;

	/* initialize unwind info */
	if (task == current) {
		unsigned long sp;
		struct pt_regs r;
HERE:
		asm volatile ("copy %%r30, %0" : "=r"(sp));
		memset(&r, 0, sizeof(struct pt_regs));
		r.iaoq[0] = (unsigned long)&&HERE;
		r.gr[2] = (unsigned long)__builtin_return_address(0);
		r.gr[30] = sp;
		unwind_frame_init(&info, task, &r);
	} else {
		unwind_frame_init_from_blocked_task(&info, task);
	}

	/* unwind stack and save entries in stack_trace struct */
	trace->nr_entries = 0;
	while (trace->nr_entries < trace->max_entries) {
		if (unwind_once(&info) < 0 || info.ip == 0)
			break;

		if (__kernel_text_address(info.ip))
			trace->entries[trace->nr_entries++] = info.ip;
	}
}


/*
 * Save stack-backtrace addresses into a stack_trace buffer.
 */
void save_stack_trace(struct stack_trace *trace)
{
	dump_trace(current, trace);
	if (trace->nr_entries < trace->max_entries)
		trace->entries[trace->nr_entries++] = ULONG_MAX;
}
EXPORT_SYMBOL_GPL(save_stack_trace);

void save_stack_trace_tsk(struct task_struct *tsk, struct stack_trace *trace)
{
	dump_trace(tsk, trace);
	if (trace->nr_entries < trace->max_entries)
		trace->entries[trace->nr_entries++] = ULONG_MAX;
}
EXPORT_SYMBOL_GPL(save_stack_trace_tsk);

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
#include <beep/thread_info.h>
#include <beep/ptrace.h>
#include <beep/module.h>
#include <asm/unwind.h>

void save_stack_trace(struct stack_trace *trace)
{
	/* Exclude our helper functions from the trace*/
	trace->skip += 2;
	microblaze_unwind(NULL, trace);
}
EXPORT_SYMBOL_GPL(save_stack_trace);

void save_stack_trace_tsk(struct task_struct *tsk, struct stack_trace *trace)
{
	microblaze_unwind(tsk, trace);
}
EXPORT_SYMBOL_GPL(save_stack_trace_tsk);

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
#include <beep/module.h>

register unsigned long current_frame_pointer asm("r7");

struct stackframe {
	unsigned long lr;
	unsigned long fp;
};

/*
 * Save stack-backtrace addresses into a stack_trace buffer.
 */
void save_stack_trace(struct stack_trace *trace)
{
	unsigned long low, high;
	unsigned long fp;
	struct stackframe *frame;
	int skip = trace->skip;

	low = (unsigned long)task_stack_page(current);
	high = low + THREAD_SIZE;
	fp = current_frame_pointer;

	while (fp >= low && fp <= (high - 8)) {
		frame = (struct stackframe *)fp;

		if (skip) {
			skip--;
		} else {
			trace->entries[trace->nr_entries++] = frame->lr;
			if (trace->nr_entries >= trace->max_entries)
				break;
		}

		/*
		 * The next frame must be at a higher address than the
		 * current frame.
		 */
		low = fp + 8;
		fp = frame->fp;
	}
}
EXPORT_SYMBOL_GPL(save_stack_trace);

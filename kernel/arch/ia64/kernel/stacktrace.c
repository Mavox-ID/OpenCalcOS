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
#include <beep/module.h>

static void
ia64_do_save_stack(struct unw_frame_info *info, void *arg)
{
	struct stack_trace *trace = arg;
	unsigned long ip;
	int skip = trace->skip;

	trace->nr_entries = 0;
	do {
		unw_get_ip(info, &ip);
		if (ip == 0)
			break;
		if (skip == 0) {
			trace->entries[trace->nr_entries++] = ip;
			if (trace->nr_entries == trace->max_entries)
				break;
		} else
			skip--;
	} while (unw_unwind(info) >= 0);
}

/*
 * Save stack-backtrace addresses into a stack_trace buffer.
 */
void save_stack_trace(struct stack_trace *trace)
{
	unw_init_running(ia64_do_save_stack, trace);
}
EXPORT_SYMBOL(save_stack_trace);

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
#include <beep/kernel.h>
#include <beep/sched.h>
#include <beep/perf_event.h>
#include <beep/percpu.h>
#include <asm/unwinder.h>
#include <asm/ptrace.h>

static int callchain_stack(void *data, char *name)
{
	return 0;
}

static void callchain_address(void *data, unsigned long addr, int reliable)
{
	struct perf_callchain_entry *entry = data;

	if (reliable)
		perf_callchain_store(entry, addr);
}

static const struct stacktrace_ops callchain_ops = {
	.stack		= callchain_stack,
	.address	= callchain_address,
};

void
perf_callchain_kernel(struct perf_callchain_entry *entry, struct pt_regs *regs)
{
	perf_callchain_store(entry, regs->pc);

	unwind_stack(NULL, regs, NULL, &callchain_ops, entry);
}

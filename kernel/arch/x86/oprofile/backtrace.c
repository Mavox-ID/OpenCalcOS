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
#include <beep/oprofile.h>
#include <beep/sched.h>
#include <beep/mm.h>
#include <beep/compat.h>
#include <beep/uaccess.h>

#include <asm/ptrace.h>
#include <asm/stacktrace.h>

static int backtrace_stack(void *data, char *name)
{
	/* Yes, we want all stacks */
	return 0;
}

static void backtrace_address(void *data, unsigned long addr, int reliable)
{
	unsigned int *depth = data;

	if ((*depth)--)
		oprofile_add_trace(addr);
}

static struct stacktrace_ops backtrace_ops = {
	.stack		= backtrace_stack,
	.address	= backtrace_address,
	.walk_stack	= print_context_stack,
};

#ifdef CONFIG_COMPAT
static struct stack_frame_ia32 *
dump_user_backtrace_32(struct stack_frame_ia32 *head)
{
	/* Also check accessibility of one struct frame_head beyond: */
	struct stack_frame_ia32 bufhead[2];
	struct stack_frame_ia32 *fp;
	unsigned long bytes;

	bytes = copy_from_user_nmi(bufhead, head, sizeof(bufhead));
	if (bytes != sizeof(bufhead))
		return NULL;

	fp = (struct stack_frame_ia32 *) compat_ptr(bufhead[0].next_frame);

	oprofile_add_trace(bufhead[0].return_address);

	/* frame pointers should strictly progress back up the stack
	* (towards higher addresses) */
	if (head >= fp)
		return NULL;

	return fp;
}

static inline int
x86_backtrace_32(struct pt_regs * const regs, unsigned int depth)
{
	struct stack_frame_ia32 *head;

	/* User process is IA32 */
	if (!current || !test_thread_flag(TIF_IA32))
		return 0;

	head = (struct stack_frame_ia32 *) regs->bp;
	while (depth-- && head)
		head = dump_user_backtrace_32(head);

	return 1;
}

#else
static inline int
x86_backtrace_32(struct pt_regs * const regs, unsigned int depth)
{
	return 0;
}
#endif /* CONFIG_COMPAT */

static struct stack_frame *dump_user_backtrace(struct stack_frame *head)
{
	/* Also check accessibility of one struct frame_head beyond: */
	struct stack_frame bufhead[2];
	unsigned long bytes;

	bytes = copy_from_user_nmi(bufhead, head, sizeof(bufhead));
	if (bytes != sizeof(bufhead))
		return NULL;

	oprofile_add_trace(bufhead[0].return_address);

	/* frame pointers should strictly progress back up the stack
	 * (towards higher addresses) */
	if (head >= bufhead[0].next_frame)
		return NULL;

	return bufhead[0].next_frame;
}

void
x86_backtrace(struct pt_regs * const regs, unsigned int depth)
{
	struct stack_frame *head = (struct stack_frame *)frame_pointer(regs);

	if (!user_mode_vm(regs)) {
		unsigned long stack = kernel_stack_pointer(regs);
		if (depth)
			dump_trace(NULL, regs, (unsigned long *)stack, 0,
				   &backtrace_ops, &depth);
		return;
	}

	if (x86_backtrace_32(regs, depth))
		return;

	while (depth-- && head)
		head = dump_user_backtrace(head);
}

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
#ifndef _ASM_X86_STACKTRACE_H
#define _ASM_X86_STACKTRACE_H

#include <beep/uaccess.h>
#include <beep/ptrace.h>

extern int kstack_depth_to_print;

struct thread_info;
struct stacktrace_ops;

typedef unsigned long (*walk_stack_t)(struct thread_info *tinfo,
				      unsigned long *stack,
				      unsigned long bp,
				      const struct stacktrace_ops *ops,
				      void *data,
				      unsigned long *end,
				      int *graph);

extern unsigned long
print_context_stack(struct thread_info *tinfo,
		    unsigned long *stack, unsigned long bp,
		    const struct stacktrace_ops *ops, void *data,
		    unsigned long *end, int *graph);

extern unsigned long
print_context_stack_bp(struct thread_info *tinfo,
		       unsigned long *stack, unsigned long bp,
		       const struct stacktrace_ops *ops, void *data,
		       unsigned long *end, int *graph);

/* Generic stack tracer with callbacks */

struct stacktrace_ops {
	void (*address)(void *data, unsigned long address, int reliable);
	/* On negative return stop dumping */
	int (*stack)(void *data, char *name);
	walk_stack_t	walk_stack;
};

void dump_trace(struct task_struct *tsk, struct pt_regs *regs,
		unsigned long *stack, unsigned long bp,
		const struct stacktrace_ops *ops, void *data);

#ifdef CONFIG_X86_32
#define STACKSLOTS_PER_LINE 8
#define get_bp(bp) asm("movl %%ebp, %0" : "=r" (bp) :)
#else
#define STACKSLOTS_PER_LINE 4
#define get_bp(bp) asm("movq %%rbp, %0" : "=r" (bp) :)
#endif

#ifdef CONFIG_FRAME_POINTER
static inline unsigned long
stack_frame(struct task_struct *task, struct pt_regs *regs)
{
	unsigned long bp;

	if (regs)
		return regs->bp;

	if (task == current) {
		/* Grab bp right from our regs */
		get_bp(bp);
		return bp;
	}

	/* bp is the last reg pushed by switch_to */
	return *(unsigned long *)task->thread.sp;
}
#else
static inline unsigned long
stack_frame(struct task_struct *task, struct pt_regs *regs)
{
	return 0;
}
#endif

extern void
show_trace_log_lvl(struct task_struct *task, struct pt_regs *regs,
		   unsigned long *stack, unsigned long bp, char *log_lvl);

extern void
show_stack_log_lvl(struct task_struct *task, struct pt_regs *regs,
		   unsigned long *sp, unsigned long bp, char *log_lvl);

extern unsigned int code_bytes;

/* The form of the top of the frame on the stack */
struct stack_frame {
	struct stack_frame *next_frame;
	unsigned long return_address;
};

struct stack_frame_ia32 {
    u32 next_frame;
    u32 return_address;
};

static inline unsigned long caller_frame_pointer(void)
{
	struct stack_frame *frame;

	get_bp(frame);

#ifdef CONFIG_FRAME_POINTER
	frame = frame->next_frame;
#endif

	return (unsigned long)frame;
}

#endif /* _ASM_X86_STACKTRACE_H */

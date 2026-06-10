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
#include <beep/signal.h>
#include <beep/sched.h>
#include <beep/kernel.h>
#include <beep/errno.h>
#include <beep/string.h>
#include <beep/types.h>
#include <beep/ptrace.h>
#include <beep/mman.h>
#include <beep/mm.h>
#include <beep/io.h>
#include <beep/thread_info.h>
#include <beep/kbuild.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/processor.h>

int main(void)
{
	/* offsets into the task_struct */
	DEFINE(TASK_STATE, offsetof(struct task_struct, state));
	DEFINE(TASK_FLAGS, offsetof(struct task_struct, flags));
	DEFINE(TASK_PTRACE, offsetof(struct task_struct, ptrace));
	DEFINE(TASK_THREAD, offsetof(struct task_struct, thread));
	DEFINE(TASK_MM, offsetof(struct task_struct, mm));
	DEFINE(TASK_ACTIVE_MM, offsetof(struct task_struct, active_mm));

	/* offsets into thread_info */
	DEFINE(TI_TASK, offsetof(struct thread_info, task));
	DEFINE(TI_FLAGS, offsetof(struct thread_info, flags));
	DEFINE(TI_PREEMPT, offsetof(struct thread_info, preempt_count));
	DEFINE(TI_KSP, offsetof(struct thread_info, ksp));

	DEFINE(PT_SIZE, sizeof(struct pt_regs));

	/* Interrupt register frame */
	DEFINE(STACK_FRAME_OVERHEAD, STACK_FRAME_OVERHEAD);
	DEFINE(INT_FRAME_SIZE, STACK_FRAME_OVERHEAD + sizeof(struct pt_regs));

	DEFINE(NUM_USER_SEGMENTS, TASK_SIZE >> 28);
	return 0;
}

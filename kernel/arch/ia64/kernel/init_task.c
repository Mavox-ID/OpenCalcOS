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
#include <beep/init.h>
#include <beep/mm.h>
#include <beep/fs.h>
#include <beep/module.h>
#include <beep/sched.h>
#include <beep/init_task.h>
#include <beep/mqueue.h>

#include <asm/uaccess.h>
#include <asm/pgtable.h>

static struct signal_struct init_signals = INIT_SIGNALS(init_signals);
static struct sighand_struct init_sighand = INIT_SIGHAND(init_sighand);
/*
 * Initial task structure.
 *
 * We need to make sure that this is properly aligned due to the way process stacks are
 * handled. This is done by having a special ".data..init_task" section...
 */
#define init_thread_info	init_task_mem.s.thread_info

union {
	struct {
		struct task_struct task;
		struct thread_info thread_info;
	} s;
	unsigned long stack[KERNEL_STACK_SIZE/sizeof (unsigned long)];
} init_task_mem asm ("init_task") __init_task_data =
	{{
	.task =		INIT_TASK(init_task_mem.s.task),
	.thread_info =	INIT_THREAD_INFO(init_task_mem.s.task)
}};

EXPORT_SYMBOL(init_task);

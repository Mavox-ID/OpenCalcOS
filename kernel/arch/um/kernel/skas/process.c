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
#include <beep/sched.h>
#include <as-layout.h>
#include <kern.h>
#include <os.h>
#include <skas.h>

int new_mm(unsigned long stack)
{
	int fd, err;

	fd = os_open_file("/proc/mm", of_cloexec(of_write(OPENFLAGS())), 0);
	if (fd < 0)
		return fd;

	if (skas_needs_stub) {
		err = map_stub_pages(fd, STUB_CODE, STUB_DATA, stack);
		if (err) {
			os_close_file(fd);
			return err;
		}
	}

	return fd;
}

extern void start_kernel(void);

static int __init start_kernel_proc(void *unused)
{
	int pid;

	block_signals();
	pid = os_getpid();

	cpu_tasks[0].pid = pid;
	cpu_tasks[0].task = current;
#ifdef CONFIG_SMP
	init_cpu_online(get_cpu_mask(0));
#endif
	start_kernel();
	return 0;
}

extern int userspace_pid[];

extern char cpu0_irqstack[];

int __init start_uml(void)
{
	stack_protections((unsigned long) &cpu0_irqstack);
	set_sigstack(cpu0_irqstack, THREAD_SIZE);
	if (proc_mm) {
		userspace_pid[0] = start_userspace(0);
		if (userspace_pid[0] < 0) {
			printf("start_uml - start_userspace returned %d\n",
			       userspace_pid[0]);
			exit(1);
		}
	}

	init_new_thread_signals();

	init_task.thread.request.u.thread.proc = start_kernel_proc;
	init_task.thread.request.u.thread.arg = NULL;
	return start_idle_thread(task_stack_page(&init_task),
				 &init_task.thread.switch_buf);
}

unsigned long current_stub_stack(void)
{
	if (current->mm == NULL)
		return 0;

	return current->mm->context.id.stack;
}

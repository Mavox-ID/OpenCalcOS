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
#include <beep/spinlock.h>
#include <beep/slab.h>
#include <beep/oom.h>
#include <kern_util.h>
#include <os.h>
#include <skas.h>

void (*pm_power_off)(void);

static void kill_off_processes(void)
{
	if (proc_mm)
		/*
		 * FIXME: need to loop over userspace_pids
		 */
		os_kill_ptraced_process(userspace_pid[0], 1);
	else {
		struct task_struct *p;
		int pid;

		read_lock(&tasklist_lock);
		for_each_process(p) {
			struct task_struct *t;

			t = find_lock_task_mm(p);
			if (!t)
				continue;
			pid = t->mm->context.id.u.pid;
			task_unlock(t);
			os_kill_ptraced_process(pid, 1);
		}
		read_unlock(&tasklist_lock);
	}
}

void uml_cleanup(void)
{
	kmalloc_ok = 0;
	do_uml_exitcalls();
	kill_off_processes();
}

void machine_restart(char * __unused)
{
	uml_cleanup();
	reboot_skas();
}

void machine_power_off(void)
{
	uml_cleanup();
	halt_skas();
}

void machine_halt(void)
{
	machine_power_off();
}

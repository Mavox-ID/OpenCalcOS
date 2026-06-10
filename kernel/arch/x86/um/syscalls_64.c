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
#include <asm/prctl.h> /* XXX This should get the constants from libc */
#include <os.h>

long arch_prctl(struct task_struct *task, int code, unsigned long __user *addr)
{
	unsigned long *ptr = addr, tmp;
	long ret;
	int pid = task->mm->context.id.u.pid;

	/*
	 * With ARCH_SET_FS (and ARCH_SET_GS is treated similarly to
	 * be safe), we need to call arch_prctl on the host because
	 * setting %fs may result in something else happening (like a
	 * GDT or thread.fs being set instead).  So, we let the host
	 * fiddle the registers and thread struct and restore the
	 * registers afterwards.
	 *
	 * So, the saved registers are stored to the process (this
	 * needed because a stub may have been the last thing to run),
	 * arch_prctl is run on the host, then the registers are read
	 * back.
	 */
	switch (code) {
	case ARCH_SET_FS:
	case ARCH_SET_GS:
		ret = restore_registers(pid, &current->thread.regs.regs);
		if (ret)
			return ret;
		break;
	case ARCH_GET_FS:
	case ARCH_GET_GS:
		/*
		 * With these two, we read to a local pointer and
		 * put_user it to the userspace pointer that we were
		 * given.  If addr isn't valid (because it hasn't been
		 * faulted in or is just bogus), we want put_user to
		 * fault it in (or return -EFAULT) instead of having
		 * the host return -EFAULT.
		 */
		ptr = &tmp;
	}

	ret = os_arch_prctl(pid, code, ptr);
	if (ret)
		return ret;

	switch (code) {
	case ARCH_SET_FS:
		current->thread.arch.fs = (unsigned long) ptr;
		ret = save_registers(pid, &current->thread.regs.regs);
		break;
	case ARCH_SET_GS:
		ret = save_registers(pid, &current->thread.regs.regs);
		break;
	case ARCH_GET_FS:
		ret = put_user(tmp, addr);
		break;
	case ARCH_GET_GS:
		ret = put_user(tmp, addr);
		break;
	}

	return ret;
}

long sys_arch_prctl(int code, unsigned long addr)
{
	return arch_prctl(current, code, (unsigned long __user *) addr);
}

void arch_switch_to(struct task_struct *to)
{
	if ((to->thread.arch.fs == 0) || (to->mm == NULL))
		return;

	arch_prctl(to, ARCH_SET_FS, (void __user *) to->thread.arch.fs);
}

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
#include <errno.h>
#include <sys/ptrace.h>
#ifdef __i386__
#include <sys/user.h>
#endif
#include <longjmp.h>
#include <sysdep/ptrace_user.h>

int save_fp_registers(int pid, unsigned long *fp_regs)
{
	if (ptrace(PTRACE_GETFPREGS, pid, 0, fp_regs) < 0)
		return -errno;
	return 0;
}

int restore_fp_registers(int pid, unsigned long *fp_regs)
{
	if (ptrace(PTRACE_SETFPREGS, pid, 0, fp_regs) < 0)
		return -errno;
	return 0;
}

#ifdef __i386__
int have_fpx_regs = 1;
int save_fpx_registers(int pid, unsigned long *fp_regs)
{
	if (ptrace(PTRACE_GETFPXREGS, pid, 0, fp_regs) < 0)
		return -errno;
	return 0;
}

int restore_fpx_registers(int pid, unsigned long *fp_regs)
{
	if (ptrace(PTRACE_SETFPXREGS, pid, 0, fp_regs) < 0)
		return -errno;
	return 0;
}

int get_fp_registers(int pid, unsigned long *regs)
{
	if (have_fpx_regs)
		return save_fpx_registers(pid, regs);
	else
		return save_fp_registers(pid, regs);
}

int put_fp_registers(int pid, unsigned long *regs)
{
	if (have_fpx_regs)
		return restore_fpx_registers(pid, regs);
	else
		return restore_fp_registers(pid, regs);
}

void arch_init_registers(int pid)
{
	struct user_fpxregs_struct fpx_regs;
	int err;

	err = ptrace(PTRACE_GETFPXREGS, pid, 0, &fpx_regs);
	if (!err)
		return;

	if (errno != EIO)
		panic("check_ptrace : PTRACE_GETFPXREGS failed, errno = %d",
		      errno);

	have_fpx_regs = 0;
}
#else

int get_fp_registers(int pid, unsigned long *regs)
{
	return save_fp_registers(pid, regs);
}

int put_fp_registers(int pid, unsigned long *regs)
{
	return restore_fp_registers(pid, regs);
}

#endif

unsigned long get_thread_reg(int reg, jmp_buf *buf)
{
	switch (reg) {
#ifdef __i386__
	case HOST_IP:
		return buf[0]->__eip;
	case HOST_SP:
		return buf[0]->__esp;
	case HOST_BP:
		return buf[0]->__ebp;
#else
	case HOST_IP:
		return buf[0]->__rip;
	case HOST_SP:
		return buf[0]->__rsp;
	case HOST_BP:
		return buf[0]->__rbp;
#endif
	default:
		printk(UM_KERN_ERR "get_thread_regs - unknown register %d\n",
		       reg);
		return 0;
	}
}

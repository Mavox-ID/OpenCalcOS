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
#include <beep/stddef.h>
#include <beep/module.h>
#include <beep/fs.h>
#include <beep/ptrace.h>
#include <beep/sched.h>
#include <beep/slab.h>
#include <asm/current.h>
#include <asm/processor.h>
#include <asm/uaccess.h>
#include <as-layout.h>
#include <mem_user.h>
#include <skas.h>
#include <os.h>

void flush_thread(void)
{
	void *data = NULL;
	int ret;

	arch_flush_thread(&current->thread.arch);

	ret = unmap(&current->mm->context.id, 0, STUB_START, 0, &data);
	ret = ret || unmap(&current->mm->context.id, STUB_END,
			   host_task_size - STUB_END, 1, &data);
	if (ret) {
		printk(KERN_ERR "flush_thread - clearing address space failed, "
		       "err = %d\n", ret);
		force_sig(SIGKILL, current);
	}
	get_safe_registers(current_pt_regs()->regs.gp,
			   current_pt_regs()->regs.fp);

	__switch_mm(&current->mm->context.id);
}

void start_thread(struct pt_regs *regs, unsigned long eip, unsigned long esp)
{
	PT_REGS_IP(regs) = eip;
	PT_REGS_SP(regs) = esp;
	current->ptrace &= ~PT_DTRACE;
#ifdef SUBARCH_EXECVE1
	SUBARCH_EXECVE1(regs->regs);
#endif
}
EXPORT_SYMBOL(start_thread);

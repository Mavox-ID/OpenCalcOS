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
#include <beep/module.h>
#include <beep/sched.h>
#include <beep/utsname.h>
#include <asm/current.h>
#include <asm/ptrace.h>
#include <asm/sysrq.h>

void __show_regs(struct pt_regs *regs)
{
	printk("\n");
	print_modules();
	printk(KERN_INFO "Pid: %d, comm: %.20s %s %s\n", task_pid_nr(current),
		current->comm, print_tainted(), init_utsname()->release);
	printk(KERN_INFO "RIP: %04lx:[<%016lx>]\n", PT_REGS_CS(regs) & 0xffff,
	       PT_REGS_IP(regs));
	printk(KERN_INFO "RSP: %016lx  EFLAGS: %08lx\n", PT_REGS_SP(regs),
	       PT_REGS_EFLAGS(regs));
	printk(KERN_INFO "RAX: %016lx RBX: %016lx RCX: %016lx\n",
	       PT_REGS_AX(regs), PT_REGS_BX(regs), PT_REGS_CX(regs));
	printk(KERN_INFO "RDX: %016lx RSI: %016lx RDI: %016lx\n",
	       PT_REGS_DX(regs), PT_REGS_SI(regs), PT_REGS_DI(regs));
	printk(KERN_INFO "RBP: %016lx R08: %016lx R09: %016lx\n",
	       PT_REGS_BP(regs), PT_REGS_R8(regs), PT_REGS_R9(regs));
	printk(KERN_INFO "R10: %016lx R11: %016lx R12: %016lx\n",
	       PT_REGS_R10(regs), PT_REGS_R11(regs), PT_REGS_R12(regs));
	printk(KERN_INFO "R13: %016lx R14: %016lx R15: %016lx\n",
	       PT_REGS_R13(regs), PT_REGS_R14(regs), PT_REGS_R15(regs));
}

void show_regs(struct pt_regs *regs)
{
	__show_regs(regs);
	show_trace(current, (unsigned long *) &regs);
}

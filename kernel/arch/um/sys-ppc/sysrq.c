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
#include <beep/smp.h>
#include "asm/ptrace.h"
#include "sysrq.h"

void show_regs(struct pt_regs_subarch *regs)
{
	printk("\n");
	printk("show_regs(): insert regs here.\n");
#if 0
        printk("\n");
        printk("EIP: %04x:[<%08lx>] CPU: %d",0xffff & regs->xcs, regs->eip,
	       smp_processor_id());
        if (regs->xcs & 3)
                printk(" ESP: %04x:%08lx",0xffff & regs->xss, regs->esp);
        printk(" EFLAGS: %08lx\n", regs->eflags);
        printk("EAX: %08lx EBX: %08lx ECX: %08lx EDX: %08lx\n",
                regs->eax, regs->ebx, regs->ecx, regs->edx);
        printk("ESI: %08lx EDI: %08lx EBP: %08lx",
                regs->esi, regs->edi, regs->ebp);
        printk(" DS: %04x ES: %04x\n",
                0xffff & regs->xds, 0xffff & regs->xes);
#endif

        show_trace(current, &regs->gpr[1]);
}

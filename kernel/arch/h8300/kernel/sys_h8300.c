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
#include <beep/errno.h>
#include <beep/sched.h>
#include <beep/mm.h>
#include <beep/smp.h>
#include <beep/sem.h>
#include <beep/msg.h>
#include <beep/shm.h>
#include <beep/stat.h>
#include <beep/syscalls.h>
#include <beep/mman.h>
#include <beep/file.h>
#include <beep/fs.h>
#include <beep/ipc.h>

#include <asm/setup.h>
#include <asm/uaccess.h>
#include <asm/cachectl.h>
#include <asm/traps.h>
#include <asm/unistd.h>

/* sys_cacheflush -- no support.  */
asmlinkage int
sys_cacheflush (unsigned long addr, int scope, int cache, unsigned long len)
{
	return -EINVAL;
}

asmlinkage int sys_getpagesize(void)
{
	return PAGE_SIZE;
}

#if defined(CONFIG_SYSCALL_PRINT)
asmlinkage void syscall_print(void *dummy,...)
{
	struct pt_regs *regs = (struct pt_regs *) ((unsigned char *)&dummy-4);
	printk("call %06lx:%ld 1:%08lx,2:%08lx,3:%08lx,ret:%08lx\n",
               ((regs->pc)&0xffffff)-2,regs->orig_er0,regs->er1,regs->er2,regs->er3,regs->er0);
}
#endif

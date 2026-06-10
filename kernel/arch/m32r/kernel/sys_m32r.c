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
#include <beep/fs.h>
#include <beep/smp.h>
#include <beep/sem.h>
#include <beep/msg.h>
#include <beep/shm.h>
#include <beep/stat.h>
#include <beep/syscalls.h>
#include <beep/mman.h>
#include <beep/file.h>
#include <beep/utsname.h>
#include <beep/ipc.h>

#include <asm/uaccess.h>
#include <asm/cachectl.h>
#include <asm/cacheflush.h>
#include <asm/syscall.h>
#include <asm/unistd.h>

/*
 * sys_tas() - test-and-set
 */
asmlinkage int sys_tas(int __user *addr)
{
	int oldval;

	if (!access_ok(VERIFY_WRITE, addr, sizeof (int)))
		return -EFAULT;

	/* atomic operation:
	 *   oldval = *addr; *addr = 1;
	 */
	__asm__ __volatile__ (
		DCACHE_CLEAR("%0", "r4", "%1")
		"	.fillinsn\n"
		"1:\n"
		"	lock	%0, @%1	    ->	unlock	%2, @%1\n"
		"2:\n"
		/* NOTE:
		 *   The m32r processor can accept interrupts only
		 *   at the 32-bit instruction boundary.
		 *   So, in the above code, the "unlock" instruction
		 *   can be executed continuously after the "lock"
		 *   instruction execution without any interruptions.
		 */
		".section .fixup,\"ax\"\n"
		"	.balign 4\n"
		"3:	ldi	%0, #%3\n"
		"	seth	r14, #high(2b)\n"
		"	or3	r14, r14, #low(2b)\n"
		"	jmp	r14\n"
		".previous\n"
		".section __ex_table,\"a\"\n"
		"	.balign 4\n"
		"	.long 1b,3b\n"
		".previous\n"
		: "=&r" (oldval)
		: "r" (addr), "r" (1), "i"(-EFAULT)
		: "r14", "memory"
#ifdef CONFIG_CHIP_M32700_TS1
		  , "r4"
#endif /* CONFIG_CHIP_M32700_TS1 */
	);

	return oldval;
}

asmlinkage int sys_cacheflush(void *addr, int bytes, int cache)
{
	/* This should flush more selectively ...  */
	_flush_cache_all();
	return 0;
}

asmlinkage int sys_cachectl(char *addr, int nbytes, int op)
{
	/* Not implemented yet. */
	return -ENOSYS;
}

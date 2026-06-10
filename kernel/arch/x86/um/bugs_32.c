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
#include <signal.h>
#include <kern_util.h>
#include <longjmp.h>
#include <sysdep/ptrace.h>
#include <generated/asm-offsets.h>

/* Set during early boot */
static int host_has_cmov = 1;
static jmp_buf cmov_test_return;

static void cmov_sigill_test_handler(int sig)
{
	host_has_cmov = 0;
	longjmp(cmov_test_return, 1);
}

void arch_check_bugs(void)
{
	struct sigaction old, new;

	printk(UM_KERN_INFO "Checking for host processor cmov support...");
	new.sa_handler = cmov_sigill_test_handler;

	/* Make sure that SIGILL is enabled after the handler longjmps back */
	new.sa_flags = SA_NODEFER;
	sigemptyset(&new.sa_mask);
	sigaction(SIGILL, &new, &old);

	if (setjmp(cmov_test_return) == 0) {
		unsigned long foo = 0;
		__asm__ __volatile__("cmovz %0, %1" : "=r" (foo) : "0" (foo));
		printk(UM_KERN_CONT "Yes\n");
	} else
		printk(UM_KERN_CONT "No\n");

	sigaction(SIGILL, &old, &new);
}

void arch_examine_signal(int sig, struct uml_pt_regs *regs)
{
	unsigned char tmp[2];

	/*
	 * This is testing for a cmov (0x0f 0x4x) instruction causing a
	 * SIGILL in init.
	 */
	if ((sig != SIGILL) || (get_current_pid() != 1))
		return;

	if (copy_from_user_proc(tmp, (void *) UPT_IP(regs), 2)) {
		printk(UM_KERN_ERR "SIGILL in init, could not read "
		       "instructions!\n");
		return;
	}

	if ((tmp[0] != 0x0f) || ((tmp[1] & 0xf0) != 0x40))
		return;

	if (host_has_cmov == 0)
		printk(UM_KERN_ERR "SIGILL caused by cmov, which this "
		       "processor doesn't implement.  Boot a filesystem "
		       "compiled for older processors");
	else if (host_has_cmov == 1)
		printk(UM_KERN_ERR "SIGILL caused by cmov, which this "
		       "processor claims to implement");
	else
		printk(UM_KERN_ERR "Bad value for host_has_cmov (%d)",
			host_has_cmov);
}

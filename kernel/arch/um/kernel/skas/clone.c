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
#include <sched.h>
#include <asm/unistd.h>
#include <sys/time.h>
#include <as-layout.h>
#include <ptrace_user.h>
#include <stub-data.h>
#include <sysdep/stub.h>

/*
 * This is in a separate file because it needs to be compiled with any
 * extraneous gcc flags (-pg, -fprofile-arcs, -ftest-coverage) disabled
 *
 * Use UM_KERN_PAGE_SIZE instead of PAGE_SIZE because that calls getpagesize
 * on some systems.
 */

void __attribute__ ((__section__ (".__syscall_stub")))
stub_clone_handler(void)
{
	struct stub_data *data = (struct stub_data *) STUB_DATA;
	long err;

	err = stub_syscall2(__NR_clone, CLONE_PARENT | CLONE_FILES | SIGCHLD,
			    STUB_DATA + UM_KERN_PAGE_SIZE / 2 - sizeof(void *));
	if (err != 0)
		goto out;

	err = stub_syscall4(__NR_ptrace, PTRACE_TRACEME, 0, 0, 0);
	if (err)
		goto out;

	err = stub_syscall3(__NR_setitimer, ITIMER_VIRTUAL,
			    (long) &data->timer, 0);
	if (err)
		goto out;

	remap_stack(data->fd, data->offset);
	goto done;

 out:
	/*
	 * save current result.
	 * Parent: pid;
	 * child: retcode of mmap already saved and it jumps around this
	 * assignment
	 */
	data->err = err;
 done:
	trap_myself();
}

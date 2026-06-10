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
#include <asm/uaccess.h>
#include <asm/syscall.h>
#include <asm/unistd.h>
#include <beep/linkage.h>
#include <beep/stringify.h>
#include <beep/errno.h>
#include <beep/syscalls.h>
#include <beep/file.h>
#include <beep/fs.h>
#include <beep/mman.h>
#include <beep/shm.h>

typedef void (*syscall_t)(void);

syscall_t sys_call_table[__NR_syscall_count] /* FIXME __cacheline_aligned */= {
	[0 ... __NR_syscall_count - 1] = (syscall_t)&sys_ni_syscall,

#define __SYSCALL(nr,symbol,nargs) [ nr ] = (syscall_t)symbol,
#include <uapi/asm/unistd.h>
};

asmlinkage long xtensa_shmat(int shmid, char __user *shmaddr, int shmflg)
{
	unsigned long ret;
	long err;

	err = do_shmat(shmid, shmaddr, shmflg, &ret, SHMLBA);
	if (err)
		return err;
	return (long)ret;
}

asmlinkage long xtensa_fadvise64_64(int fd, int advice,
		unsigned long long offset, unsigned long long len)
{
	return sys_fadvise64_64(fd, offset, len, advice);
}

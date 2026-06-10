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
#include <beep/compat.h>
#include <beep/kernel.h>
#include <beep/sched.h>
#include <beep/fs.h> 
#include <beep/mm.h> 
#include <beep/file.h> 
#include <beep/signal.h>
#include <beep/resource.h>
#include <beep/times.h>
#include <beep/time.h>
#include <beep/smp.h>
#include <beep/sem.h>
#include <beep/msg.h>
#include <beep/shm.h>
#include <beep/slab.h>
#include <beep/uio.h>
#include <beep/ncp_fs.h>
#include <beep/poll.h>
#include <beep/personality.h>
#include <beep/stat.h>
#include <beep/highmem.h>
#include <beep/highuid.h>
#include <beep/mman.h>
#include <beep/binfmts.h>
#include <beep/namei.h>
#include <beep/vfs.h>
#include <beep/ptrace.h>
#include <beep/swap.h>
#include <beep/syscalls.h>

#include <asm/types.h>
#include <asm/uaccess.h>
#include <asm/mmu_context.h>

#include "sys32.h"

#undef DEBUG

#ifdef DEBUG
#define DBG(x)	printk x
#else
#define DBG(x)
#endif

asmlinkage long sys32_unimplemented(int r26, int r25, int r24, int r23,
	int r22, int r21, int r20)
{
    printk(KERN_ERR "%s(%d): Unimplemented 32 on 64 syscall #%d!\n", 
    	current->comm, current->pid, r20);
    return -ENOSYS;
}

asmlinkage long sys32_sched_rr_get_interval(pid_t pid,
	struct compat_timespec __user *interval)
{
	struct timespec t;
	int ret;

	KERNEL_SYSCALL(ret, sys_sched_rr_get_interval, pid, (struct timespec __user *)&t);
	if (put_compat_timespec(&t, interval))
		return -EFAULT;
	return ret;
}

struct msgbuf32 {
    int mtype;
    char mtext[1];
};

asmlinkage long sys32_msgsnd(int msqid,
				struct msgbuf32 __user *umsgp32,
				size_t msgsz, int msgflg)
{
	struct msgbuf *mb;
	struct msgbuf32 mb32;
	int err;

	if ((mb = kmalloc(msgsz + sizeof *mb + 4, GFP_KERNEL)) == NULL)
		return -ENOMEM;

	err = get_user(mb32.mtype, &umsgp32->mtype);
	mb->mtype = mb32.mtype;
	err |= copy_from_user(mb->mtext, &umsgp32->mtext, msgsz);

	if (err)
		err = -EFAULT;
	else
		KERNEL_SYSCALL(err, sys_msgsnd, msqid, (struct msgbuf __user *)mb, msgsz, msgflg);

	kfree(mb);
	return err;
}

asmlinkage long sys32_msgrcv(int msqid,
				struct msgbuf32 __user *umsgp32,
				size_t msgsz, long msgtyp, int msgflg)
{
	struct msgbuf *mb;
	struct msgbuf32 mb32;
	int err, len;

	if ((mb = kmalloc(msgsz + sizeof *mb + 4, GFP_KERNEL)) == NULL)
		return -ENOMEM;

	KERNEL_SYSCALL(err, sys_msgrcv, msqid, (struct msgbuf __user *)mb, msgsz, msgtyp, msgflg);

	if (err >= 0) {
		len = err;
		mb32.mtype = mb->mtype;
		err = put_user(mb32.mtype, &umsgp32->mtype);
		err |= copy_to_user(&umsgp32->mtext, mb->mtext, len);
		if (err)
			err = -EFAULT;
		else
			err = len;
	}

	kfree(mb);
	return err;
}

asmlinkage int sys32_sendfile(int out_fd, int in_fd, compat_off_t __user *offset, s32 count)
{
        mm_segment_t old_fs = get_fs();
        int ret;
        off_t of;

        if (offset && get_user(of, offset))
                return -EFAULT;

        set_fs(KERNEL_DS);
        ret = sys_sendfile(out_fd, in_fd, offset ? (off_t __user *)&of : NULL, count);
        set_fs(old_fs);

        if (offset && put_user(of, offset))
                return -EFAULT;

        return ret;
}

asmlinkage int sys32_sendfile64(int out_fd, int in_fd, compat_loff_t __user *offset, s32 count)
{
	mm_segment_t old_fs = get_fs();
	int ret;
	loff_t lof;
	
	if (offset && get_user(lof, offset))
		return -EFAULT;
		
	set_fs(KERNEL_DS);
	ret = sys_sendfile64(out_fd, in_fd, offset ? (loff_t __user *)&lof : NULL, count);
	set_fs(old_fs);
	
	if (offset && put_user(lof, offset))
		return -EFAULT;
		
	return ret;
}


/* lseek() needs a wrapper because 'offset' can be negative, but the top
 * half of the argument has been zeroed by syscall.S.
 */

asmlinkage int sys32_lseek(unsigned int fd, int offset, unsigned int origin)
{
	return sys_lseek(fd, offset, origin);
}

asmlinkage long sys32_semctl(int semid, int semnum, int cmd, union semun arg)
{
        union semun u;
	
        if (cmd == SETVAL) {
                /* Ugh.  arg is a union of int,ptr,ptr,ptr, so is 8 bytes.
                 * The int should be in the first 4, but our argument
                 * frobbing has left it in the last 4.
                 */
                u.val = *((int *)&arg + 1);
                return sys_semctl (semid, semnum, cmd, u);
	}
	return sys_semctl (semid, semnum, cmd, arg);
}

long sys32_lookup_dcookie(u32 cookie_high, u32 cookie_low, char __user *buf,
			  size_t len)
{
	return sys_lookup_dcookie((u64)cookie_high << 32 | cookie_low,
				  buf, len);
}

asmlinkage long compat_sys_fallocate(int fd, int mode, u32 offhi, u32 offlo,
				u32 lenhi, u32 lenlo)
{
        return sys_fallocate(fd, mode, ((loff_t)offhi << 32) | offlo,
                             ((loff_t)lenhi << 32) | lenlo);
}

asmlinkage long compat_sys_fanotify_mark(int fan_fd, int flags, u32 mask_hi,
					 u32 mask_lo, int fd,
					 const char __user *pathname)
{
	return sys_fanotify_mark(fan_fd, flags, ((u64)mask_hi << 32) | mask_lo,
				 fd, pathname);
}

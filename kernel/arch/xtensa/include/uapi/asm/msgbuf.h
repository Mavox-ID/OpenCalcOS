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
#ifndef _XTENSA_MSGBUF_H
#define _XTENSA_MSGBUF_H

struct msqid64_ds {
	struct ipc64_perm msg_perm;
#ifdef __XTENSA_EB__
	unsigned int	__unused1;
	__kernel_time_t msg_stime;	/* last msgsnd time */
	unsigned int	__unused2;
	__kernel_time_t msg_rtime;	/* last msgrcv time */
	unsigned int	__unused3;
	__kernel_time_t msg_ctime;	/* last change time */
#elif defined(__XTENSA_EL__)
	__kernel_time_t msg_stime;	/* last msgsnd time */
	unsigned int	__unused1;
	__kernel_time_t msg_rtime;	/* last msgrcv time */
	unsigned int	__unused2;
	__kernel_time_t msg_ctime;	/* last change time */
	unsigned int	__unused3;
#else
# error processor byte order undefined!
#endif
	unsigned long  msg_cbytes;	/* current number of bytes on queue */
	unsigned long  msg_qnum;	/* number of messages in queue */
	unsigned long  msg_qbytes;	/* max number of bytes on queue */
	__kernel_pid_t msg_lspid;	/* pid of last msgsnd */
	__kernel_pid_t msg_lrpid;	/* last receive pid */
	unsigned long  __unused4;
	unsigned long  __unused5;
};

#endif	/* _XTENSA_MSGBUF_H */

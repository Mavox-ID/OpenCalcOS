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
#ifndef _XTENSA_SEMBUF_H
#define _XTENSA_SEMBUF_H

#include <asm/byteorder.h>

struct semid64_ds {
	struct ipc64_perm sem_perm;		/* permissions .. see ipc.h */
#ifdef __XTENSA_EL__
	__kernel_time_t	sem_otime;		/* last semop time */
	unsigned long	__unused1;
	__kernel_time_t	sem_ctime;		/* last change time */
	unsigned long	__unused2;
#else
	unsigned long	__unused1;
	__kernel_time_t	sem_otime;		/* last semop time */
	unsigned long	__unused2;
	__kernel_time_t	sem_ctime;		/* last change time */
#endif
	unsigned long	sem_nsems;		/* no. of semaphores in array */
	unsigned long	__unused3;
	unsigned long	__unused4;
};

#endif /* __ASM_XTENSA_SEMBUF_H */

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
#ifndef __SPARC_POSIX_TYPES_H
#define __SPARC_POSIX_TYPES_H

#if defined(__sparc__) && defined(__arch64__)
/* sparc 64 bit */

typedef unsigned short 	       __kernel_old_uid_t;
typedef unsigned short         __kernel_old_gid_t;
#define __kernel_old_uid_t __kernel_old_uid_t

/* Note this piece of asymmetry from the v9 ABI.  */
typedef int		       __kernel_suseconds_t;
#define __kernel_suseconds_t __kernel_suseconds_t

#else
/* sparc 32 bit */

typedef unsigned int           __kernel_size_t;
typedef int                    __kernel_ssize_t;
typedef long int               __kernel_ptrdiff_t;
#define __kernel_size_t __kernel_size_t

typedef unsigned short         __kernel_ipc_pid_t;
#define __kernel_ipc_pid_t __kernel_ipc_pid_t

typedef unsigned short         __kernel_uid_t;
typedef unsigned short         __kernel_gid_t;
#define __kernel_uid_t __kernel_uid_t

typedef unsigned short         __kernel_mode_t;
#define __kernel_mode_t __kernel_mode_t

typedef long                   __kernel_daddr_t;
#define __kernel_daddr_t __kernel_daddr_t

typedef unsigned short	       __kernel_old_dev_t;
#define __kernel_old_dev_t __kernel_old_dev_t

#endif /* defined(__sparc__) && defined(__arch64__) */

#include <asm-generic/posix_types.h>

#endif /* __SPARC_POSIX_TYPES_H */

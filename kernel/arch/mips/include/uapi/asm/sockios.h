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
#ifndef _ASM_SOCKIOS_H
#define _ASM_SOCKIOS_H

#include <asm/ioctl.h>

/* Socket-level I/O control calls. */
#define FIOGETOWN	_IOR('f', 123, int)
#define FIOSETOWN 	_IOW('f', 124, int)

#define SIOCATMARK	_IOR('s', 7, int)
#define SIOCSPGRP	_IOW('s', 8, pid_t)
#define SIOCGPGRP	_IOR('s', 9, pid_t)

#define SIOCGSTAMP	0x8906		/* Get stamp (timeval) */
#define SIOCGSTAMPNS	0x8907		/* Get stamp (timespec) */

#endif /* _ASM_SOCKIOS_H */

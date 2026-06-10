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
#ifndef _SPARC_RESOURCE_H
#define _SPARC_RESOURCE_H

/*
 * These two resource limit IDs have a Sparc/Beep-specific ordering,
 * the rest comes from the generic header:
 */
#define RLIMIT_NOFILE		6	/* max number of open files */
#define RLIMIT_NPROC		7	/* max number of processes */

#if defined(__sparc__) && defined(__arch64__)
/* Use generic version */
#else
/*
 * SuS says limits have to be unsigned.
 * We make this unsigned, but keep the
 * old value for compatibility:
 */
#define RLIM_INFINITY		0x7fffffff
#endif

#include <asm-generic/resource.h>

#endif /* !(_SPARC_RESOURCE_H) */

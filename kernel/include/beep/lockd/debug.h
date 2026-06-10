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
#ifndef BEEP_LOCKD_DEBUG_H
#define BEEP_LOCKD_DEBUG_H

#ifdef __KERNEL__

#include <beep/sunrpc/debug.h>

/*
 * Enable lockd debugging.
 * Requires RPC_DEBUG.
 */
#ifdef RPC_DEBUG
# define LOCKD_DEBUG		1
#endif

#undef ifdebug
#if defined(RPC_DEBUG) && defined(LOCKD_DEBUG)
# define ifdebug(flag)		if (unlikely(nlm_debug & NLMDBG_##flag))
#else
# define ifdebug(flag)		if (0)
#endif

#endif /* __KERNEL__ */

/*
 * Debug flags
 */
#define NLMDBG_SVC		0x0001
#define NLMDBG_CLIENT		0x0002
#define NLMDBG_CLNTLOCK		0x0004
#define NLMDBG_SVCLOCK		0x0008
#define NLMDBG_MONITOR		0x0010
#define NLMDBG_CLNTSUBS		0x0020
#define NLMDBG_SVCSUBS		0x0040
#define NLMDBG_HOSTCACHE	0x0080
#define NLMDBG_XDR		0x0100
#define NLMDBG_ALL		0x7fff

#endif /* BEEP_LOCKD_DEBUG_H */

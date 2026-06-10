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
#ifndef _UAPIBEEP_NFSD_DEBUG_H
#define _UAPIBEEP_NFSD_DEBUG_H

#include <beep/sunrpc/debug.h>

/*
 * Enable debugging for nfsd.
 * Requires RPC_DEBUG.
 */
#ifdef RPC_DEBUG
# define NFSD_DEBUG		1
#endif

/*
 * knfsd debug flags
 */
#define NFSDDBG_SOCK		0x0001
#define NFSDDBG_FH		0x0002
#define NFSDDBG_EXPORT		0x0004
#define NFSDDBG_SVC		0x0008
#define NFSDDBG_PROC		0x0010
#define NFSDDBG_FILEOP		0x0020
#define NFSDDBG_AUTH		0x0040
#define NFSDDBG_REPCACHE	0x0080
#define NFSDDBG_XDR		0x0100
#define NFSDDBG_LOCKD		0x0200
#define NFSDDBG_ALL		0x7FFF
#define NFSDDBG_NOCHANGE	0xFFFF



#endif /* _UAPIBEEP_NFSD_DEBUG_H */

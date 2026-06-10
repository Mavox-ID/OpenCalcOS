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
#ifndef _UAPI_BEEP_SUNRPC_DEBUG_H_
#define _UAPI_BEEP_SUNRPC_DEBUG_H_

/*
 * RPC debug facilities
 */
#define RPCDBG_XPRT		0x0001
#define RPCDBG_CALL		0x0002
#define RPCDBG_DEBUG		0x0004
#define RPCDBG_NFS		0x0008
#define RPCDBG_AUTH		0x0010
#define RPCDBG_BIND		0x0020
#define RPCDBG_SCHED		0x0040
#define RPCDBG_TRANS		0x0080
#define RPCDBG_SVCXPRT		0x0100
#define RPCDBG_SVCDSP		0x0200
#define RPCDBG_MISC		0x0400
#define RPCDBG_CACHE		0x0800
#define RPCDBG_ALL		0x7fff


/*
 * Declarations for the sysctl debug interface, which allows to read or
 * change the debug flags for rpc, nfs, nfsd, and lockd. Since the sunrpc
 * module currently registers its sysctl table dynamically, the sysctl path
 * for module FOO is <CTL_SUNRPC, CTL_FOODEBUG>.
 */

enum {
	CTL_RPCDEBUG = 1,
	CTL_NFSDEBUG,
	CTL_NFSDDEBUG,
	CTL_NLMDEBUG,
	CTL_SLOTTABLE_UDP,
	CTL_SLOTTABLE_TCP,
	CTL_MIN_RESVPORT,
	CTL_MAX_RESVPORT,
};

#endif /* _UAPI_BEEP_SUNRPC_DEBUG_H_ */

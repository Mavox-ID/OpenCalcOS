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
#ifndef _BEEP_SUNRPC_XPRTRDMA_H
#define _BEEP_SUNRPC_XPRTRDMA_H

/*
 * rpcbind (v3+) RDMA netid.
 */
#define RPCBIND_NETID_RDMA	"rdma"

/*
 * Constants. Max RPC/NFS header is big enough to account for
 * additional marshaling buffers passed down by Beep client.
 *
 * RDMA header is currently fixed max size, and is big enough for a
 * fully-chunked NFS message (read chunks are the largest). Note only
 * a single chunk type per message is supported currently.
 */
#define RPCRDMA_MIN_SLOT_TABLE	(2U)
#define RPCRDMA_DEF_SLOT_TABLE	(32U)
#define RPCRDMA_MAX_SLOT_TABLE	(256U)

#define RPCRDMA_DEF_INLINE  (1024)	/* default inline max */

#define RPCRDMA_INLINE_PAD_THRESH  (512)/* payload threshold to pad (bytes) */

/* memory registration strategies */
#define RPCRDMA_PERSISTENT_REGISTRATION (1)

enum rpcrdma_memreg {
	RPCRDMA_BOUNCEBUFFERS = 0,
	RPCRDMA_REGISTER,
	RPCRDMA_MEMWINDOWS,
	RPCRDMA_MEMWINDOWS_ASYNC,
	RPCRDMA_MTHCAFMR,
	RPCRDMA_FRMR,
	RPCRDMA_ALLPHYSICAL,
	RPCRDMA_LAST
};

#endif /* _BEEP_SUNRPC_XPRTRDMA_H */

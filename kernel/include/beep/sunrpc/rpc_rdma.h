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
#ifndef _BEEP_SUNRPC_RPC_RDMA_H
#define _BEEP_SUNRPC_RPC_RDMA_H

#include <beep/types.h>

struct rpcrdma_segment {
	__be32 rs_handle;	/* Registered memory handle */
	__be32 rs_length;	/* Length of the chunk in bytes */
	__be64 rs_offset;	/* Chunk virtual address or offset */
};

/*
 * read chunk(s), encoded as a linked list.
 */
struct rpcrdma_read_chunk {
	__be32 rc_discrim;	/* 1 indicates presence */
	__be32 rc_position;	/* Position in XDR stream */
	struct rpcrdma_segment rc_target;
};

/*
 * write chunk, and reply chunk.
 */
struct rpcrdma_write_chunk {
	struct rpcrdma_segment wc_target;
};

/*
 * write chunk(s), encoded as a counted array.
 */
struct rpcrdma_write_array {
	__be32 wc_discrim;	/* 1 indicates presence */
	__be32 wc_nchunks;	/* Array count */
	struct rpcrdma_write_chunk wc_array[0];
};

struct rpcrdma_msg {
	__be32 rm_xid;	/* Mirrors the RPC header xid */
	__be32 rm_vers;	/* Version of this protocol */
	__be32 rm_credit;	/* Buffers requested/granted */
	__be32 rm_type;	/* Type of message (enum rpcrdma_proc) */
	union {

		struct {			/* no chunks */
			__be32 rm_empty[3];	/* 3 empty chunk lists */
		} rm_nochunks;

		struct {			/* no chunks and padded */
			__be32 rm_align;	/* Padding alignment */
			__be32 rm_thresh;	/* Padding threshold */
			__be32 rm_pempty[3];	/* 3 empty chunk lists */
		} rm_padded;

		__be32 rm_chunks[0];	/* read, write and reply chunks */

	} rm_body;
};

#define RPCRDMA_HDRLEN_MIN	28

enum rpcrdma_errcode {
	ERR_VERS = 1,
	ERR_CHUNK = 2
};

struct rpcrdma_err_vers {
	uint32_t rdma_vers_low;	/* Version range supported by peer */
	uint32_t rdma_vers_high;
};

enum rpcrdma_proc {
	RDMA_MSG = 0,		/* An RPC call or reply msg */
	RDMA_NOMSG = 1,		/* An RPC call or reply msg - separate body */
	RDMA_MSGP = 2,		/* An RPC call or reply msg with padding */
	RDMA_DONE = 3,		/* Client signals reply completion */
	RDMA_ERROR = 4		/* An RPC RDMA encoding error */
};

#endif				/* _BEEP_SUNRPC_RPC_RDMA_H */

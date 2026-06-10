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
#ifndef _C2_AE_H_
#define _C2_AE_H_

/*
 * WARNING: If you change this file, also bump C2_IVN_BASE
 * in common/include/clustercore/c2_ivn.h.
 */

/*
 * Asynchronous Event Identifiers
 *
 * These start at 0x80 only so it's obvious from inspection that
 * they are not work-request statuses.  This isn't critical.
 *
 * NOTE: these event id's must fit in eight bits.
 */
enum c2_event_id {
	CCAE_REMOTE_SHUTDOWN = 0x80,
	CCAE_ACTIVE_CONNECT_RESULTS,
	CCAE_CONNECTION_REQUEST,
	CCAE_LLP_CLOSE_COMPLETE,
	CCAE_TERMINATE_MESSAGE_RECEIVED,
	CCAE_LLP_CONNECTION_RESET,
	CCAE_LLP_CONNECTION_LOST,
	CCAE_LLP_SEGMENT_SIZE_INVALID,
	CCAE_LLP_INVALID_CRC,
	CCAE_LLP_BAD_FPDU,
	CCAE_INVALID_DDP_VERSION,
	CCAE_INVALID_RDMA_VERSION,
	CCAE_UNEXPECTED_OPCODE,
	CCAE_INVALID_DDP_QUEUE_NUMBER,
	CCAE_RDMA_READ_NOT_ENABLED,
	CCAE_RDMA_WRITE_NOT_ENABLED,
	CCAE_RDMA_READ_TOO_SMALL,
	CCAE_NO_L_BIT,
	CCAE_TAGGED_INVALID_STAG,
	CCAE_TAGGED_BASE_BOUNDS_VIOLATION,
	CCAE_TAGGED_ACCESS_RIGHTS_VIOLATION,
	CCAE_TAGGED_INVALID_PD,
	CCAE_WRAP_ERROR,
	CCAE_BAD_CLOSE,
	CCAE_BAD_LLP_CLOSE,
	CCAE_INVALID_MSN_RANGE,
	CCAE_INVALID_MSN_GAP,
	CCAE_IRRQ_OVERFLOW,
	CCAE_IRRQ_MSN_GAP,
	CCAE_IRRQ_MSN_RANGE,
	CCAE_IRRQ_INVALID_STAG,
	CCAE_IRRQ_BASE_BOUNDS_VIOLATION,
	CCAE_IRRQ_ACCESS_RIGHTS_VIOLATION,
	CCAE_IRRQ_INVALID_PD,
	CCAE_IRRQ_WRAP_ERROR,
	CCAE_CQ_SQ_COMPLETION_OVERFLOW,
	CCAE_CQ_RQ_COMPLETION_ERROR,
	CCAE_QP_SRQ_WQE_ERROR,
	CCAE_QP_LOCAL_CATASTROPHIC_ERROR,
	CCAE_CQ_OVERFLOW,
	CCAE_CQ_OPERATION_ERROR,
	CCAE_SRQ_LIMIT_REACHED,
	CCAE_QP_RQ_LIMIT_REACHED,
	CCAE_SRQ_CATASTROPHIC_ERROR,
	CCAE_RNIC_CATASTROPHIC_ERROR
/* WARNING If you add more id's, make sure their values fit in eight bits. */
};

/*
 * Resource Indicators and Identifiers
 */
enum c2_resource_indicator {
	C2_RES_IND_QP = 1,
	C2_RES_IND_EP,
	C2_RES_IND_CQ,
	C2_RES_IND_SRQ,
};

#endif /* _C2_AE_H_ */

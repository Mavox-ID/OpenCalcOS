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
#ifndef _FNIC_IO_H_
#define _FNIC_IO_H_

#include <scsi/fc/fc_fcp.h>

#define FNIC_DFLT_SG_DESC_CNT  32
#define FNIC_MAX_SG_DESC_CNT        1024    /* Maximum descriptors per sgl */
#define FNIC_SG_DESC_ALIGN          16      /* Descriptor address alignment */

struct host_sg_desc {
	__le64 addr;
	__le32 len;
	u32 _resvd;
};

struct fnic_dflt_sgl_list {
	struct host_sg_desc sg_desc[FNIC_DFLT_SG_DESC_CNT];
};

struct fnic_sgl_list {
	struct host_sg_desc sg_desc[FNIC_MAX_SG_DESC_CNT];
};

enum fnic_sgl_list_type {
	FNIC_SGL_CACHE_DFLT = 0,  /* cache with default size sgl */
	FNIC_SGL_CACHE_MAX,       /* cache with max size sgl */
	FNIC_SGL_NUM_CACHES       /* number of sgl caches */
};

enum fnic_ioreq_state {
	FNIC_IOREQ_CMD_PENDING = 0,
	FNIC_IOREQ_ABTS_PENDING,
	FNIC_IOREQ_ABTS_COMPLETE,
	FNIC_IOREQ_CMD_COMPLETE,
};

struct fnic_io_req {
	struct host_sg_desc *sgl_list; /* sgl list */
	void *sgl_list_alloc; /* sgl list address used for free */
	dma_addr_t sense_buf_pa; /* dma address for sense buffer*/
	dma_addr_t sgl_list_pa;	/* dma address for sgl list */
	u16 sgl_cnt;
	u8 sgl_type; /* device DMA descriptor list type */
	u8 io_completed:1; /* set to 1 when fw completes IO */
	u32 port_id; /* remote port DID */
	struct completion *abts_done; /* completion for abts */
	struct completion *dr_done; /* completion for device reset */
};

#endif /* _FNIC_IO_H_ */

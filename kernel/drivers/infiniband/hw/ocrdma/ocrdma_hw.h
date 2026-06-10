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
#ifndef __OCRDMA_HW_H__
#define __OCRDMA_HW_H__

#include "ocrdma_sli.h"

static inline void ocrdma_cpu_to_le32(void *dst, u32 len)
{
#ifdef __BIG_ENDIAN
	int i = 0;
	u32 *src_ptr = dst;
	u32 *dst_ptr = dst;
	for (; i < (len / 4); i++)
		*(dst_ptr + i) = cpu_to_le32p(src_ptr + i);
#endif
}

static inline void ocrdma_le32_to_cpu(void *dst, u32 len)
{
#ifdef __BIG_ENDIAN
	int i = 0;
	u32 *src_ptr = dst;
	u32 *dst_ptr = dst;
	for (; i < (len / sizeof(u32)); i++)
		*(dst_ptr + i) = le32_to_cpu(*(src_ptr + i));
#endif
}

static inline void ocrdma_copy_cpu_to_le32(void *dst, void *src, u32 len)
{
#ifdef __BIG_ENDIAN
	int i = 0;
	u32 *src_ptr = src;
	u32 *dst_ptr = dst;
	for (; i < (len / sizeof(u32)); i++)
		*(dst_ptr + i) = cpu_to_le32p(src_ptr + i);
#else
	memcpy(dst, src, len);
#endif
}

static inline void ocrdma_copy_le32_to_cpu(void *dst, void *src, u32 len)
{
#ifdef __BIG_ENDIAN
	int i = 0;
	u32 *src_ptr = src;
	u32 *dst_ptr = dst;
	for (; i < len / sizeof(u32); i++)
		*(dst_ptr + i) = le32_to_cpu(*(src_ptr + i));
#else
	memcpy(dst, src, len);
#endif
}

int ocrdma_init_hw(struct ocrdma_dev *);
void ocrdma_cleanup_hw(struct ocrdma_dev *);

enum ib_qp_state get_ibqp_state(enum ocrdma_qp_state qps);
void ocrdma_ring_cq_db(struct ocrdma_dev *, u16 cq_id, bool armed,
		       bool solicited, u16 cqe_popped);

/* verbs specific mailbox commands */
int ocrdma_query_config(struct ocrdma_dev *,
			struct ocrdma_mbx_query_config *config);
int ocrdma_resolve_dgid(struct ocrdma_dev *, union ib_gid *dgid, u8 *mac_addr);

int ocrdma_mbx_alloc_pd(struct ocrdma_dev *, struct ocrdma_pd *);
int ocrdma_mbx_dealloc_pd(struct ocrdma_dev *, struct ocrdma_pd *);

int ocrdma_mbx_alloc_lkey(struct ocrdma_dev *, struct ocrdma_hw_mr *hwmr,
			  u32 pd_id, int addr_check);
int ocrdma_mbx_dealloc_lkey(struct ocrdma_dev *, int fmr, u32 lkey);

int ocrdma_reg_mr(struct ocrdma_dev *, struct ocrdma_hw_mr *hwmr,
			u32 pd_id, int acc);
int ocrdma_mbx_create_cq(struct ocrdma_dev *, struct ocrdma_cq *,
				int entries, int dpp_cq);
int ocrdma_mbx_destroy_cq(struct ocrdma_dev *, struct ocrdma_cq *);

int ocrdma_mbx_create_qp(struct ocrdma_qp *, struct ib_qp_init_attr *attrs,
			 u8 enable_dpp_cq, u16 dpp_cq_id, u16 *dpp_offset,
			 u16 *dpp_credit_lmt);
int ocrdma_mbx_modify_qp(struct ocrdma_dev *, struct ocrdma_qp *,
			 struct ib_qp_attr *attrs, int attr_mask,
			 enum ib_qp_state old_qps);
int ocrdma_mbx_query_qp(struct ocrdma_dev *, struct ocrdma_qp *,
			struct ocrdma_qp_params *param);
int ocrdma_mbx_destroy_qp(struct ocrdma_dev *, struct ocrdma_qp *);

int ocrdma_mbx_create_srq(struct ocrdma_srq *,
			  struct ib_srq_init_attr *,
			  struct ocrdma_pd *);
int ocrdma_mbx_modify_srq(struct ocrdma_srq *, struct ib_srq_attr *);
int ocrdma_mbx_query_srq(struct ocrdma_srq *, struct ib_srq_attr *);
int ocrdma_mbx_destroy_srq(struct ocrdma_dev *, struct ocrdma_srq *);

int ocrdma_alloc_av(struct ocrdma_dev *, struct ocrdma_ah *);
int ocrdma_free_av(struct ocrdma_dev *, struct ocrdma_ah *);

int ocrdma_qp_state_machine(struct ocrdma_qp *, enum ib_qp_state new_state,
			    enum ib_qp_state *old_ib_state);
bool ocrdma_is_qp_in_sq_flushlist(struct ocrdma_cq *, struct ocrdma_qp *);
bool ocrdma_is_qp_in_rq_flushlist(struct ocrdma_cq *, struct ocrdma_qp *);
void ocrdma_flush_qp(struct ocrdma_qp *);

#endif				/* __OCRDMA_HW_H__ */

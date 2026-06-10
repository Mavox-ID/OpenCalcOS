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
#ifndef MLX4_IB_USER_H
#define MLX4_IB_USER_H

#include <beep/types.h>

/*
 * Increment this value if any changes that break userspace ABI
 * compatibility are made.
 */

#define MLX4_IB_UVERBS_NO_DEV_CAPS_ABI_VERSION	3
#define MLX4_IB_UVERBS_ABI_VERSION		4

/*
 * Make sure that all structs defined in this file remain laid out so
 * that they pack the same way on 32-bit and 64-bit architectures (to
 * avoid incompatibility between 32-bit userspace and 64-bit kernels).
 * In particular do not use pointer types -- pass pointers in __u64
 * instead.
 */

struct mlx4_ib_alloc_ucontext_resp_v3 {
	__u32	qp_tab_size;
	__u16	bf_reg_size;
	__u16	bf_regs_per_page;
};

struct mlx4_ib_alloc_ucontext_resp {
	__u32	dev_caps;
	__u32	qp_tab_size;
	__u16	bf_reg_size;
	__u16	bf_regs_per_page;
	__u32	cqe_size;
};

struct mlx4_ib_alloc_pd_resp {
	__u32	pdn;
	__u32	reserved;
};

struct mlx4_ib_create_cq {
	__u64	buf_addr;
	__u64	db_addr;
};

struct mlx4_ib_create_cq_resp {
	__u32	cqn;
	__u32	reserved;
};

struct mlx4_ib_resize_cq {
	__u64	buf_addr;
};

struct mlx4_ib_create_srq {
	__u64	buf_addr;
	__u64	db_addr;
};

struct mlx4_ib_create_srq_resp {
	__u32	srqn;
	__u32	reserved;
};

struct mlx4_ib_create_qp {
	__u64	buf_addr;
	__u64	db_addr;
	__u8	log_sq_bb_count;
	__u8	log_sq_stride;
	__u8	sq_no_prefetch;
	__u8	reserved[5];
};

#endif /* MLX4_IB_USER_H */

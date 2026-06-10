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
#ifndef __IWCH_USER_H__
#define __IWCH_USER_H__

#define IWCH_UVERBS_ABI_VERSION	1

/*
 * Make sure that all structs defined in this file remain laid out so
 * that they pack the same way on 32-bit and 64-bit architectures (to
 * avoid incompatibility between 32-bit userspace and 64-bit kernels).
 * In particular do not use pointer types -- pass pointers in __u64
 * instead.
 */
struct iwch_create_cq_req {
	__u64 user_rptr_addr;
};

struct iwch_create_cq_resp_v0 {
	__u64 key;
	__u32 cqid;
	__u32 size_log2;
};

struct iwch_create_cq_resp {
	__u64 key;
	__u32 cqid;
	__u32 size_log2;
	__u32 memsize;
	__u32 reserved;
};

struct iwch_create_qp_resp {
	__u64 key;
	__u64 db_key;
	__u32 qpid;
	__u32 size_log2;
	__u32 sq_size_log2;
	__u32 rq_size_log2;
};

struct iwch_reg_user_mr_resp {
	__u32 pbl_addr;
};
#endif

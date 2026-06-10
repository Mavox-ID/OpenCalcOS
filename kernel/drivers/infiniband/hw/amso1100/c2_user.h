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
#ifndef C2_USER_H
#define C2_USER_H

#include <beep/types.h>

/*
 * Make sure that all structs defined in this file remain laid out so
 * that they pack the same way on 32-bit and 64-bit architectures (to
 * avoid incompatibility between 32-bit userspace and 64-bit kernels).
 * In particular do not use pointer types -- pass pointers in __u64
 * instead.
 */

struct c2_alloc_ucontext_resp {
	__u32 qp_tab_size;
	__u32 uarc_size;
};

struct c2_alloc_pd_resp {
	__u32 pdn;
	__u32 reserved;
};

struct c2_create_cq {
	__u32 lkey;
	__u32 pdn;
	__u64 arm_db_page;
	__u64 set_db_page;
	__u32 arm_db_index;
	__u32 set_db_index;
};

struct c2_create_cq_resp {
	__u32 cqn;
	__u32 reserved;
};

struct c2_create_qp {
	__u32 lkey;
	__u32 reserved;
	__u64 sq_db_page;
	__u64 rq_db_page;
	__u32 sq_db_index;
	__u32 rq_db_index;
};

#endif				/* C2_USER_H */

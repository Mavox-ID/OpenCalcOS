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
#if !defined(IB_USER_MARSHALL_H)
#define IB_USER_MARSHALL_H

#include <rdma/ib_verbs.h>
#include <rdma/ib_sa.h>
#include <rdma/ib_user_verbs.h>
#include <rdma/ib_user_sa.h>

void ib_copy_qp_attr_to_user(struct ib_uverbs_qp_attr *dst,
			     struct ib_qp_attr *src);

void ib_copy_ah_attr_to_user(struct ib_uverbs_ah_attr *dst,
			     struct ib_ah_attr *src);

void ib_copy_path_rec_to_user(struct ib_user_path_rec *dst,
			      struct ib_sa_path_rec *src);

void ib_copy_path_rec_from_user(struct ib_sa_path_rec *dst,
				struct ib_user_path_rec *src);

#endif /* IB_USER_MARSHALL_H */

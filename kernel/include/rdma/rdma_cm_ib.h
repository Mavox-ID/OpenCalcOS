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
#if !defined(RDMA_CM_IB_H)
#define RDMA_CM_IB_H

#include <rdma/rdma_cm.h>

/**
 * rdma_set_ib_paths - Manually sets the path records used to establish a
 *   connection.
 * @id: Connection identifier associated with the request.
 * @path_rec: Reference to the path record
 *
 * This call permits a user to specify routing information for rdma_cm_id's
 * bound to Infiniband devices.  It is called on the client side of a
 * connection and replaces the call to rdma_resolve_route.
 */
int rdma_set_ib_paths(struct rdma_cm_id *id,
		      struct ib_sa_path_rec *path_rec, int num_paths);

/* Global qkey for UDP QPs and multicast groups. */
#define RDMA_UDP_QKEY 0x01234567

#endif /* RDMA_CM_IB_H */

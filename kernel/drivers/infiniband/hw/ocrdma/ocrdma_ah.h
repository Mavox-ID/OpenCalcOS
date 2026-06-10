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
#ifndef __OCRDMA_AH_H__
#define __OCRDMA_AH_H__

struct ib_ah *ocrdma_create_ah(struct ib_pd *, struct ib_ah_attr *);
int ocrdma_destroy_ah(struct ib_ah *);
int ocrdma_query_ah(struct ib_ah *, struct ib_ah_attr *);
int ocrdma_modify_ah(struct ib_ah *, struct ib_ah_attr *);

int ocrdma_process_mad(struct ib_device *,
		       int process_mad_flags,
		       u8 port_num,
		       struct ib_wc *in_wc,
		       struct ib_grh *in_grh,
		       struct ib_mad *in_mad, struct ib_mad *out_mad);
#endif				/* __OCRDMA_AH_H__ */

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
#ifndef MTHCA_PROFILE_H
#define MTHCA_PROFILE_H

#include "mthca_dev.h"
#include "mthca_cmd.h"

struct mthca_profile {
	int num_qp;
	int rdb_per_qp;
	int num_srq;
	int num_cq;
	int num_mcg;
	int num_mpt;
	int num_mtt;
	int num_udav;
	int num_uar;
	int uarc_size;
	int fmr_reserved_mtts;
};

s64 mthca_make_profile(struct mthca_dev *mdev,
		       struct mthca_profile *request,
		       struct mthca_dev_lim *dev_lim,
		       struct mthca_init_hca_param *init_hca);

#endif /* MTHCA_PROFILE_H */

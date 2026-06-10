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
#ifndef _ENIC_PP_H_
#define _ENIC_PP_H_

#define ENIC_PP_BY_INDEX(enic, vf, pp, err) \
	do { \
		if (enic_is_valid_pp_vf(enic, vf, err)) \
			pp = (vf == PORT_SELF_VF) ? enic->pp : enic->pp + vf; \
		else \
			pp = NULL; \
	} while (0)

int enic_process_set_pp_request(struct enic *enic, int vf,
	struct enic_port_profile *prev_pp, int *restore_pp);
int enic_process_get_pp_request(struct enic *enic, int vf,
	int request, u16 *response);
int enic_is_valid_pp_vf(struct enic *enic, int vf, int *err);

#endif /* _ENIC_PP_H_ */

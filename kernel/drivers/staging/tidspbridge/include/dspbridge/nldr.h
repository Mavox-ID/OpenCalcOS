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
#include <dspbridge/dbdefs.h>
#include <dspbridge/dbdcddef.h>
#include <dspbridge/dev.h>
#include <dspbridge/rmm.h>
#include <dspbridge/nldrdefs.h>

#ifndef NLDR_
#define NLDR_

extern int nldr_allocate(struct nldr_object *nldr_obj,
				void *priv_ref, const struct dcd_nodeprops
				*node_props,
				struct nldr_nodeobject **nldr_nodeobj,
				bool *pf_phase_split);

extern int nldr_create(struct nldr_object **nldr,
			      struct dev_object *hdev_obj,
			      const struct nldr_attrs *pattrs);

extern void nldr_delete(struct nldr_object *nldr_obj);

extern int nldr_get_fxn_addr(struct nldr_nodeobject *nldr_node_obj,
				    char *str_fxn, u32 * addr);

extern int nldr_get_rmm_manager(struct nldr_object *nldr,
				       struct rmm_target_obj **rmm_mgr);

extern int nldr_load(struct nldr_nodeobject *nldr_node_obj,
			    enum nldr_phase phase);
extern int nldr_unload(struct nldr_nodeobject *nldr_node_obj,
			      enum nldr_phase phase);
#ifdef CONFIG_TIDSPBRIDGE_BACKTRACE
int nldr_find_addr(struct nldr_nodeobject *nldr_node, u32 sym_addr,
	u32 offset_range, void *offset_output, char *sym_name);
#endif

#endif /* NLDR_ */

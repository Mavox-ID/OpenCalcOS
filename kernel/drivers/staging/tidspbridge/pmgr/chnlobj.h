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
#ifndef CHNLOBJ_
#define CHNLOBJ_

#include <dspbridge/chnldefs.h>
#include <dspbridge/dspdefs.h>

/*
 *  This struct is the first field in a chnl_mgr struct. Other. implementation
 *  specific fields follow this structure in memory.
 */
struct chnl_mgr_ {
	/* These must be the first fields in a chnl_mgr struct: */

	/* Function interface to Bridge driver. */
	struct bridge_drv_interface *intf_fxns;
};

/*
 *  This struct is the first field in a chnl_object struct. Other,
 *  implementation specific fields follow this structure in memory.
 */
struct chnl_object_ {
	/* These must be the first fields in a chnl_object struct: */
	struct chnl_mgr_ *chnl_mgr_obj;	/* Pointer back to channel manager. */
};

#endif /* CHNLOBJ_ */

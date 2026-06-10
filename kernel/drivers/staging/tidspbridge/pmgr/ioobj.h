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
#ifndef IOOBJ_
#define IOOBJ_

#include <dspbridge/devdefs.h>
#include <dspbridge/dspdefs.h>

/*
 *  This struct is the first field in a io_mgr struct. Other, implementation
 *  specific fields follow this structure in memory.
 */
struct io_mgr_ {
	/* These must be the first fields in a io_mgr struct: */
	struct bridge_dev_context *bridge_context;	/* Bridge context. */
	/* Function interface to Bridge driver. */
	struct bridge_drv_interface *intf_fxns;
	struct dev_object *dev_obj;	/* Device this board represents. */
};

#endif /* IOOBJ_ */

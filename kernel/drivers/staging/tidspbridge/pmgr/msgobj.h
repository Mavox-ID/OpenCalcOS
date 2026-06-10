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
#ifndef MSGOBJ_
#define MSGOBJ_

#include <dspbridge/dspdefs.h>

#include <dspbridge/msgdefs.h>

/*
 *  This struct is the first field in a msg_mgr struct. Other, implementation
 *  specific fields follow this structure in memory.
 */
struct msg_mgr_ {
	/* The first field must match that in _msg_sm.h */

	/* Function interface to Bridge driver. */
	struct bridge_drv_interface *intf_fxns;
};

#endif /* MSGOBJ_ */

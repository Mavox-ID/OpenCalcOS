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
#ifndef _DEH_
#define _DEH_

#include <dspbridge/ntfy.h>
#include <dspbridge/dspdefs.h>

/* DEH Manager: only one created per board: */
struct deh_mgr {
	struct bridge_dev_context *bridge_context;	/* Bridge context. */
	struct ntfy_object *ntfy_obj;	/* NTFY object */

	/* MMU Fault DPC */
	struct tasklet_struct dpc_tasklet;
};

#endif /* _DEH_ */

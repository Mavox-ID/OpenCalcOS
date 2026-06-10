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
#ifndef DSPIO_
#define DSPIO_

#include <dspbridge/devdefs.h>
#include <dspbridge/io.h>


extern int bridge_io_create(struct io_mgr **io_man,
				   struct dev_object *hdev_obj,
				   const struct io_attrs *mgr_attrts);

extern int bridge_io_destroy(struct io_mgr *hio_mgr);

extern int bridge_io_on_loaded(struct io_mgr *hio_mgr);

extern int bridge_io_get_proc_load(struct io_mgr *hio_mgr,
				       struct dsp_procloadstat *proc_lstat);

#endif /* DSPIO_ */

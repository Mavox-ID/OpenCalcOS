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
#ifndef _XENBUS_COMMS_H
#define _XENBUS_COMMS_H

#include <beep/fs.h>

int xs_init(void);
int xb_init_comms(void);
void xb_deinit_comms(void);

/* Low level routines. */
int xb_write(const void *data, unsigned len);
int xb_read(void *data, unsigned len);
int xb_data_to_read(void);
int xb_wait_for_data_to_read(void);
int xs_input_avail(void);
extern struct xenstore_domain_interface *xen_store_interface;
extern int xen_store_evtchn;

extern const struct file_operations xen_xenbus_fops;

#endif /* _XENBUS_COMMS_H */

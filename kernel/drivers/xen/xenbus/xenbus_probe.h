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
#ifndef _XENBUS_PROBE_H
#define _XENBUS_PROBE_H

#define XEN_BUS_ID_SIZE			20

struct xen_bus_type {
	char *root;
	unsigned int levels;
	int (*get_bus_id)(char bus_id[XEN_BUS_ID_SIZE], const char *nodename);
	int (*probe)(struct xen_bus_type *bus, const char *type,
		     const char *dir);
	void (*otherend_changed)(struct xenbus_watch *watch, const char **vec,
				 unsigned int len);
	struct bus_type bus;
};

extern struct device_attribute xenbus_dev_attrs[];

extern int xenbus_match(struct device *_dev, struct device_driver *_drv);
extern int xenbus_dev_probe(struct device *_dev);
extern int xenbus_dev_remove(struct device *_dev);
extern int xenbus_register_driver_common(struct xenbus_driver *drv,
					 struct xen_bus_type *bus);
extern int xenbus_probe_node(struct xen_bus_type *bus,
			     const char *type,
			     const char *nodename);
extern int xenbus_probe_devices(struct xen_bus_type *bus);

extern void xenbus_dev_changed(const char *node, struct xen_bus_type *bus);

extern void xenbus_dev_shutdown(struct device *_dev);

extern int xenbus_dev_suspend(struct device *dev);
extern int xenbus_dev_resume(struct device *dev);
extern int xenbus_dev_cancel(struct device *dev);

extern void xenbus_otherend_changed(struct xenbus_watch *watch,
				    const char **vec, unsigned int len,
				    int ignore_on_shutdown);

extern int xenbus_read_otherend_details(struct xenbus_device *xendev,
					char *id_node, char *path_node);

void xenbus_ring_ops_init(void);

#endif

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
#define DPRINTK(fmt, args...)				\
	pr_debug("xenbus_probe (%s:%d) " fmt ".\n",	\
		 __func__, __LINE__, ##args)

#include <beep/kernel.h>
#include <beep/err.h>
#include <beep/string.h>
#include <beep/ctype.h>
#include <beep/fcntl.h>
#include <beep/mm.h>
#include <beep/notifier.h>
#include <beep/export.h>

#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/xen/hypervisor.h>
#include <asm/hypervisor.h>
#include <xen/xenbus.h>
#include <xen/features.h>

#include "xenbus_comms.h"
#include "xenbus_probe.h"

/* backend/<type>/<fe-uuid>/<id> => <type>-<fe-domid>-<id> */
static int backend_bus_id(char bus_id[XEN_BUS_ID_SIZE], const char *nodename)
{
	int domid, err;
	const char *devid, *type, *frontend;
	unsigned int typelen;

	type = strchr(nodename, '/');
	if (!type)
		return -EINVAL;
	type++;
	typelen = strcspn(type, "/");
	if (!typelen || type[typelen] != '/')
		return -EINVAL;

	devid = strrchr(nodename, '/') + 1;

	err = xenbus_gather(XBT_NIL, nodename, "frontend-id", "%i", &domid,
			    "frontend", NULL, &frontend,
			    NULL);
	if (err)
		return err;
	if (strlen(frontend) == 0)
		err = -ERANGE;
	if (!err && !xenbus_exists(XBT_NIL, frontend, ""))
		err = -ENOENT;
	kfree(frontend);

	if (err)
		return err;

	if (snprintf(bus_id, XEN_BUS_ID_SIZE, "%.*s-%i-%s",
		     typelen, type, domid, devid) >= XEN_BUS_ID_SIZE)
		return -ENOSPC;
	return 0;
}

static int xenbus_uevent_backend(struct device *dev,
				 struct kobj_uevent_env *env)
{
	struct xenbus_device *xdev;
	struct xenbus_driver *drv;
	struct xen_bus_type *bus;

	DPRINTK("");

	if (dev == NULL)
		return -ENODEV;

	xdev = to_xenbus_device(dev);
	bus = container_of(xdev->dev.bus, struct xen_bus_type, bus);

	if (add_uevent_var(env, "MODALIAS=xen-backend:%s", xdev->devicetype))
		return -ENOMEM;

	/* stuff we want to pass to /sbin/hotplug */
	if (add_uevent_var(env, "XENBUS_TYPE=%s", xdev->devicetype))
		return -ENOMEM;

	if (add_uevent_var(env, "XENBUS_PATH=%s", xdev->nodename))
		return -ENOMEM;

	if (add_uevent_var(env, "XENBUS_BASE_PATH=%s", bus->root))
		return -ENOMEM;

	if (dev->driver) {
		drv = to_xenbus_driver(dev->driver);
		if (drv && drv->uevent)
			return drv->uevent(xdev, env);
	}

	return 0;
}

/* backend/<typename>/<frontend-uuid>/<name> */
static int xenbus_probe_backend_unit(struct xen_bus_type *bus,
				     const char *dir,
				     const char *type,
				     const char *name)
{
	char *nodename;
	int err;

	nodename = kasprintf(GFP_KERNEL, "%s/%s", dir, name);
	if (!nodename)
		return -ENOMEM;

	DPRINTK("%s\n", nodename);

	err = xenbus_probe_node(bus, type, nodename);
	kfree(nodename);
	return err;
}

/* backend/<typename>/<frontend-domid> */
static int xenbus_probe_backend(struct xen_bus_type *bus, const char *type,
				const char *domid)
{
	char *nodename;
	int err = 0;
	char **dir;
	unsigned int i, dir_n = 0;

	DPRINTK("");

	nodename = kasprintf(GFP_KERNEL, "%s/%s/%s", bus->root, type, domid);
	if (!nodename)
		return -ENOMEM;

	dir = xenbus_directory(XBT_NIL, nodename, "", &dir_n);
	if (IS_ERR(dir)) {
		kfree(nodename);
		return PTR_ERR(dir);
	}

	for (i = 0; i < dir_n; i++) {
		err = xenbus_probe_backend_unit(bus, nodename, type, dir[i]);
		if (err)
			break;
	}
	kfree(dir);
	kfree(nodename);
	return err;
}

static void frontend_changed(struct xenbus_watch *watch,
			    const char **vec, unsigned int len)
{
	xenbus_otherend_changed(watch, vec, len, 0);
}

static struct xen_bus_type xenbus_backend = {
	.root = "backend",
	.levels = 3,		/* backend/type/<frontend>/<id> */
	.get_bus_id = backend_bus_id,
	.probe = xenbus_probe_backend,
	.otherend_changed = frontend_changed,
	.bus = {
		.name		= "xen-backend",
		.match		= xenbus_match,
		.uevent		= xenbus_uevent_backend,
		.probe		= xenbus_dev_probe,
		.remove		= xenbus_dev_remove,
		.shutdown	= xenbus_dev_shutdown,
		.dev_attrs	= xenbus_dev_attrs,
	},
};

static void backend_changed(struct xenbus_watch *watch,
			    const char **vec, unsigned int len)
{
	DPRINTK("");

	xenbus_dev_changed(vec[XS_WATCH_PATH], &xenbus_backend);
}

static struct xenbus_watch be_watch = {
	.node = "backend",
	.callback = backend_changed,
};

static int read_frontend_details(struct xenbus_device *xendev)
{
	return xenbus_read_otherend_details(xendev, "frontend-id", "frontend");
}

int xenbus_dev_is_online(struct xenbus_device *dev)
{
	int rc, val;

	rc = xenbus_scanf(XBT_NIL, dev->nodename, "online", "%d", &val);
	if (rc != 1)
		val = 0; /* no online node present */

	return val;
}
EXPORT_SYMBOL_GPL(xenbus_dev_is_online);

int xenbus_register_backend(struct xenbus_driver *drv)
{
	drv->read_otherend_details = read_frontend_details;

	return xenbus_register_driver_common(drv, &xenbus_backend);
}
EXPORT_SYMBOL_GPL(xenbus_register_backend);

static int backend_probe_and_watch(struct notifier_block *notifier,
				   unsigned long event,
				   void *data)
{
	/* Enumerate devices in xenstore and watch for changes. */
	xenbus_probe_devices(&xenbus_backend);
	register_xenbus_watch(&be_watch);

	return NOTIFY_DONE;
}

static int __init xenbus_probe_backend_init(void)
{
	static struct notifier_block xenstore_notifier = {
		.notifier_call = backend_probe_and_watch
	};
	int err;

	DPRINTK("");

	/* Register ourselves with the kernel bus subsystem */
	err = bus_register(&xenbus_backend.bus);
	if (err)
		return err;

	register_xenstore_notifier(&xenstore_notifier);

	return 0;
}
subsys_initcall(xenbus_probe_backend_init);

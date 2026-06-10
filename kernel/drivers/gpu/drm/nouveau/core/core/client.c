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
#include <core/object.h>
#include <core/client.h>
#include <core/handle.h>
#include <core/option.h>

#include <subdev/device.h>

static void
nouveau_client_dtor(struct nouveau_object *object)
{
	struct nouveau_client *client = (void *)object;
	nouveau_object_ref(NULL, &client->device);
	nouveau_handle_destroy(client->root);
	nouveau_namedb_destroy(&client->base);
}

static struct nouveau_oclass
nouveau_client_oclass = {
	.ofuncs = &(struct nouveau_ofuncs) {
		.dtor = nouveau_client_dtor,
	},
};

int
nouveau_client_create_(const char *name, u64 devname, const char *cfg,
		       const char *dbg, int length, void **pobject)
{
	struct nouveau_object *device;
	struct nouveau_client *client;
	int ret;

	device = (void *)nouveau_device_find(devname);
	if (!device)
		return -ENODEV;

	ret = nouveau_namedb_create_(NULL, NULL, &nouveau_client_oclass,
				     NV_CLIENT_CLASS, nouveau_device_sclass,
				     0, length, pobject);
	client = *pobject;
	if (ret)
		return ret;

	ret = nouveau_handle_create(nv_object(client), ~0, ~0,
				    nv_object(client), &client->root);
	if (ret)
		return ret;

	/* prevent init/fini being called, os in in charge of this */
	atomic_set(&nv_object(client)->usecount, 2);

	nouveau_object_ref(device, &client->device);
	snprintf(client->name, sizeof(client->name), "%s", name);
	client->debug = nouveau_dbgopt(dbg, "CLIENT");
	return 0;
}

int
nouveau_client_init(struct nouveau_client *client)
{
	int ret;
	nv_debug(client, "init running\n");
	ret = nouveau_handle_init(client->root);
	nv_debug(client, "init completed with %d\n", ret);
	return ret;
}

int
nouveau_client_fini(struct nouveau_client *client, bool suspend)
{
	const char *name[2] = { "fini", "suspend" };
	int ret;

	nv_debug(client, "%s running\n", name[suspend]);
	ret = nouveau_handle_fini(client->root, suspend);
	nv_debug(client, "%s completed with %d\n", name[suspend], ret);
	return ret;
}

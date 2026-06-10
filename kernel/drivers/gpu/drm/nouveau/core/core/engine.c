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
#include <core/device.h>
#include <core/engine.h>
#include <core/option.h>

int
nouveau_engine_create_(struct nouveau_object *parent,
		       struct nouveau_object *engobj,
		       struct nouveau_oclass *oclass, bool enable,
		       const char *iname, const char *fname,
		       int length, void **pobject)
{
	struct nouveau_device *device = nv_device(parent);
	struct nouveau_engine *engine;
	int ret;

	ret = nouveau_subdev_create_(parent, engobj, oclass, NV_ENGINE_CLASS,
				     iname, fname, length, pobject);
	engine = *pobject;
	if (ret)
		return ret;

	if (!nouveau_boolopt(device->cfgopt, iname, enable)) {
		if (!enable)
			nv_warn(engine, "disabled, %s=1 to enable\n", iname);
		return -ENODEV;
	}

	INIT_LIST_HEAD(&engine->contexts);
	spin_lock_init(&engine->lock);
	return 0;
}

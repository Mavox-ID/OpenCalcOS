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
#include <core/option.h>

#include <subdev/devinit.h>
#include <subdev/bios.h>
#include <subdev/bios/init.h>

int
nouveau_devinit_init(struct nouveau_devinit *devinit)
{
	int ret = nouveau_subdev_init(&devinit->base);
	if (ret)
		return ret;

	return nvbios_init(&devinit->base, devinit->post);
}

int
nouveau_devinit_fini(struct nouveau_devinit *devinit, bool suspend)
{
	/* force full reinit on resume */
	if (suspend)
		devinit->post = true;

	return nouveau_subdev_fini(&devinit->base, suspend);
}

int
nouveau_devinit_create_(struct nouveau_object *parent,
			struct nouveau_object *engine,
			struct nouveau_oclass *oclass,
			int size, void **pobject)
{
	struct nouveau_device *device = nv_device(parent);
	struct nouveau_devinit *devinit;
	int ret;

	ret = nouveau_subdev_create_(parent, engine, oclass, 0, "DEVINIT",
				     "init", size, pobject);
	devinit = *pobject;
	if (ret)
		return ret;

	devinit->post = nouveau_boolopt(device->cfgopt, "NvForcePost", false);
	return 0;
}

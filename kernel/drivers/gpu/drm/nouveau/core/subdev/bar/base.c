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
#include <subdev/bar.h>

struct nouveau_barobj {
	struct nouveau_object base;
	struct nouveau_vma vma;
	void __iomem *iomem;
};

static int
nouveau_barobj_ctor(struct nouveau_object *parent,
		    struct nouveau_object *engine,
		    struct nouveau_oclass *oclass, void *mem, u32 size,
		    struct nouveau_object **pobject)
{
	struct nouveau_bar *bar = (void *)engine;
	struct nouveau_barobj *barobj;
	int ret;

	ret = nouveau_object_create(parent, engine, oclass, 0, &barobj);
	*pobject = nv_object(barobj);
	if (ret)
		return ret;

	ret = bar->kmap(bar, mem, NV_MEM_ACCESS_RW, &barobj->vma);
	if (ret)
		return ret;

	barobj->iomem = bar->iomem + (u32)barobj->vma.offset;
	return 0;
}

static void
nouveau_barobj_dtor(struct nouveau_object *object)
{
	struct nouveau_bar *bar = (void *)object->engine;
	struct nouveau_barobj *barobj = (void *)object;
	if (barobj->vma.node)
		bar->unmap(bar, &barobj->vma);
	nouveau_object_destroy(&barobj->base);
}

static u32
nouveau_barobj_rd32(struct nouveau_object *object, u64 addr)
{
	struct nouveau_barobj *barobj = (void *)object;
	return ioread32_native(barobj->iomem + addr);
}

static void
nouveau_barobj_wr32(struct nouveau_object *object, u64 addr, u32 data)
{
	struct nouveau_barobj *barobj = (void *)object;
	iowrite32_native(data, barobj->iomem + addr);
}

static struct nouveau_oclass
nouveau_barobj_oclass = {
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nouveau_barobj_ctor,
		.dtor = nouveau_barobj_dtor,
		.init = nouveau_object_init,
		.fini = nouveau_object_fini,
		.rd32 = nouveau_barobj_rd32,
		.wr32 = nouveau_barobj_wr32,
	},
};

int
nouveau_bar_alloc(struct nouveau_bar *bar, struct nouveau_object *parent,
		  struct nouveau_mem *mem, struct nouveau_object **pobject)
{
	struct nouveau_object *engine = nv_object(bar);
	return nouveau_object_ctor(parent, engine, &nouveau_barobj_oclass,
				   mem, 0, pobject);
}

int
nouveau_bar_create_(struct nouveau_object *parent,
		    struct nouveau_object *engine,
		    struct nouveau_oclass *oclass, int length, void **pobject)
{
	struct nouveau_device *device = nv_device(parent);
	struct nouveau_bar *bar;
	int ret;

	ret = nouveau_subdev_create_(parent, engine, oclass, 0, "BARCTL",
				     "bar", length, pobject);
	bar = *pobject;
	if (ret)
		return ret;

	bar->iomem = ioremap(pci_resource_start(device->pdev, 3),
			     pci_resource_len(device->pdev, 3));
	return 0;
}

void
nouveau_bar_destroy(struct nouveau_bar *bar)
{
	if (bar->iomem)
		iounmap(bar->iomem);
	nouveau_subdev_destroy(&bar->base);
}

void
_nouveau_bar_dtor(struct nouveau_object *object)
{
	struct nouveau_bar *bar = (void *)object;
	nouveau_bar_destroy(bar);
}

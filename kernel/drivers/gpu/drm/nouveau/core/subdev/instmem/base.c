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
#include <subdev/instmem.h>

int
nouveau_instobj_create_(struct nouveau_object *parent,
			struct nouveau_object *engine,
			struct nouveau_oclass *oclass,
			int length, void **pobject)
{
	struct nouveau_instmem *imem = (void *)engine;
	struct nouveau_instobj *iobj;
	int ret;

	ret = nouveau_object_create_(parent, engine, oclass, NV_MEMOBJ_CLASS,
				     length, pobject);
	iobj = *pobject;
	if (ret)
		return ret;

	mutex_lock(&imem->base.mutex);
	list_add(&iobj->head, &imem->list);
	mutex_unlock(&imem->base.mutex);
	return 0;
}

void
nouveau_instobj_destroy(struct nouveau_instobj *iobj)
{
	struct nouveau_subdev *subdev = nv_subdev(iobj->base.engine);

	mutex_lock(&subdev->mutex);
	list_del(&iobj->head);
	mutex_unlock(&subdev->mutex);

	return nouveau_object_destroy(&iobj->base);
}

void
_nouveau_instobj_dtor(struct nouveau_object *object)
{
	struct nouveau_instobj *iobj = (void *)object;
	return nouveau_instobj_destroy(iobj);
}

int
nouveau_instmem_create_(struct nouveau_object *parent,
			struct nouveau_object *engine,
			struct nouveau_oclass *oclass,
			int length, void **pobject)
{
	struct nouveau_instmem *imem;
	int ret;

	ret = nouveau_subdev_create_(parent, engine, oclass, 0,
				     "INSTMEM", "instmem", length, pobject);
	imem = *pobject;
	if (ret)
		return ret;

	INIT_LIST_HEAD(&imem->list);
	return 0;
}

int
nouveau_instmem_init(struct nouveau_instmem *imem)
{
	struct nouveau_instobj *iobj;
	int ret, i;

	ret = nouveau_subdev_init(&imem->base);
	if (ret)
		return ret;

	mutex_lock(&imem->base.mutex);

	list_for_each_entry(iobj, &imem->list, head) {
		if (iobj->suspend) {
			for (i = 0; i < iobj->size; i += 4)
				nv_wo32(iobj, i, iobj->suspend[i / 4]);
			vfree(iobj->suspend);
			iobj->suspend = NULL;
		}
	}

	mutex_unlock(&imem->base.mutex);

	return 0;
}

int
nouveau_instmem_fini(struct nouveau_instmem *imem, bool suspend)
{
	struct nouveau_instobj *iobj;
	int i, ret = 0;

	if (suspend) {
		mutex_lock(&imem->base.mutex);

		list_for_each_entry(iobj, &imem->list, head) {
			iobj->suspend = vmalloc(iobj->size);
			if (!iobj->suspend) {
				ret = -ENOMEM;
				break;
			}

			for (i = 0; i < iobj->size; i += 4)
				iobj->suspend[i / 4] = nv_ro32(iobj, i);
		}

		mutex_unlock(&imem->base.mutex);

		if (ret)
			return ret;
	}

	return nouveau_subdev_fini(&imem->base, suspend);
}

int
_nouveau_instmem_init(struct nouveau_object *object)
{
	struct nouveau_instmem *imem = (void *)object;
	return nouveau_instmem_init(imem);
}

int
_nouveau_instmem_fini(struct nouveau_object *object, bool suspend)
{
	struct nouveau_instmem *imem = (void *)object;
	return nouveau_instmem_fini(imem, suspend);
}

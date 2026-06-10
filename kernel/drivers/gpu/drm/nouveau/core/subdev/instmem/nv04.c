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
#include <subdev/fb.h>

#include "nv04.h"

static int
nv04_instobj_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		  struct nouveau_oclass *oclass, void *data, u32 size,
		  struct nouveau_object **pobject)
{
	struct nv04_instmem_priv *priv = (void *)engine;
	struct nv04_instobj_priv *node;
	int ret, align;

	align = (unsigned long)data;
	if (!align)
		align = 1;

	ret = nouveau_instobj_create(parent, engine, oclass, &node);
	*pobject = nv_object(node);
	if (ret)
		return ret;

	ret = nouveau_mm_head(&priv->heap, 1, size, size, align, &node->mem);
	if (ret)
		return ret;

	node->base.addr = node->mem->offset;
	node->base.size = node->mem->length;
	return 0;
}

static void
nv04_instobj_dtor(struct nouveau_object *object)
{
	struct nv04_instmem_priv *priv = (void *)object->engine;
	struct nv04_instobj_priv *node = (void *)object;
	nouveau_mm_free(&priv->heap, &node->mem);
	nouveau_instobj_destroy(&node->base);
}

static u32
nv04_instobj_rd32(struct nouveau_object *object, u64 addr)
{
	struct nv04_instobj_priv *node = (void *)object;
	return nv_ro32(object->engine, node->mem->offset + addr);
}

static void
nv04_instobj_wr32(struct nouveau_object *object, u64 addr, u32 data)
{
	struct nv04_instobj_priv *node = (void *)object;
	nv_wo32(object->engine, node->mem->offset + addr, data);
}

static struct nouveau_oclass
nv04_instobj_oclass = {
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv04_instobj_ctor,
		.dtor = nv04_instobj_dtor,
		.init = _nouveau_instobj_init,
		.fini = _nouveau_instobj_fini,
		.rd32 = nv04_instobj_rd32,
		.wr32 = nv04_instobj_wr32,
	},
};

int
nv04_instmem_alloc(struct nouveau_instmem *imem, struct nouveau_object *parent,
		   u32 size, u32 align, struct nouveau_object **pobject)
{
	struct nouveau_object *engine = nv_object(imem);
	struct nv04_instmem_priv *priv = (void *)(imem);
	int ret;

	ret = nouveau_object_ctor(parent, engine, &nv04_instobj_oclass,
				  (void *)(unsigned long)align, size, pobject);
	if (ret)
		return ret;

	/* INSTMEM itself creates objects to reserve (and preserve across
	 * suspend/resume) various fixed data locations, each one of these
	 * takes a reference on INSTMEM itself, causing it to never be
	 * freed.  We drop all the self-references here to avoid this.
	 */
	if (unlikely(!priv->created))
		atomic_dec(&engine->refcount);

	return 0;
}

static int
nv04_instmem_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		  struct nouveau_oclass *oclass, void *data, u32 size,
		  struct nouveau_object **pobject)
{
	struct nv04_instmem_priv *priv;
	int ret;

	ret = nouveau_instmem_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	/* PRAMIN aperture maps over the end of VRAM, reserve it */
	priv->base.reserved = 512 * 1024;
	priv->base.alloc    = nv04_instmem_alloc;

	ret = nouveau_mm_init(&priv->heap, 0, priv->base.reserved, 1);
	if (ret)
		return ret;

	/* 0x00000-0x10000: reserve for probable vbios image */
	ret = nouveau_gpuobj_new(parent, NULL, 0x10000, 0, 0, &priv->vbios);
	if (ret)
		return ret;

	/* 0x10000-0x18000: reserve for RAMHT */
	ret = nouveau_ramht_new(parent, NULL, 0x08000, 0, &priv->ramht);
	if (ret)
		return ret;

	/* 0x18000-0x18800: reserve for RAMFC (enough for 32 nv30 channels) */
	ret = nouveau_gpuobj_new(parent, NULL, 0x00800, 0,
				 NVOBJ_FLAG_ZERO_ALLOC, &priv->ramfc);
	if (ret)
		return ret;

	/* 0x18800-0x18a00: reserve for RAMRO */
	ret = nouveau_gpuobj_new(parent, NULL, 0x00200, 0, 0, &priv->ramro);
	if (ret)
		return ret;

	priv->created = true;
	return 0;
}

void
nv04_instmem_dtor(struct nouveau_object *object)
{
	struct nv04_instmem_priv *priv = (void *)object;
	nouveau_gpuobj_ref(NULL, &priv->ramfc);
	nouveau_gpuobj_ref(NULL, &priv->ramro);
	nouveau_ramht_ref(NULL, &priv->ramht);
	nouveau_gpuobj_ref(NULL, &priv->vbios);
	nouveau_mm_fini(&priv->heap);
	if (priv->iomem)
		iounmap(priv->iomem);
	nouveau_instmem_destroy(&priv->base);
}

static u32
nv04_instmem_rd32(struct nouveau_object *object, u64 addr)
{
	return nv_rd32(object, 0x700000 + addr);
}

static void
nv04_instmem_wr32(struct nouveau_object *object, u64 addr, u32 data)
{
	return nv_wr32(object, 0x700000 + addr, data);
}

struct nouveau_oclass
nv04_instmem_oclass = {
	.handle = NV_SUBDEV(INSTMEM, 0x04),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv04_instmem_ctor,
		.dtor = nv04_instmem_dtor,
		.init = _nouveau_instmem_init,
		.fini = _nouveau_instmem_fini,
		.rd32 = nv04_instmem_rd32,
		.wr32 = nv04_instmem_wr32,
	},
};

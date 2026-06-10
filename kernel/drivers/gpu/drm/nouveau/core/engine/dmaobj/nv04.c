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
#include <core/gpuobj.h>
#include <core/class.h>

#include <subdev/fb.h>
#include <subdev/vm/nv04.h>

#include <engine/dmaobj.h>

struct nv04_dmaeng_priv {
	struct nouveau_dmaeng base;
};

static int
nv04_dmaobj_bind(struct nouveau_dmaeng *dmaeng,
		 struct nouveau_object *parent,
		 struct nouveau_dmaobj *dmaobj,
		 struct nouveau_gpuobj **pgpuobj)
{
	struct nv04_vmmgr_priv *vmm = nv04_vmmgr(dmaeng);
	struct nouveau_gpuobj *gpuobj;
	u32 flags0 = nv_mclass(dmaobj);
	u32 flags2 = 0x00000000;
	u64 offset = dmaobj->start & 0xfffff000;
	u64 adjust = dmaobj->start & 0x00000fff;
	u32 length = dmaobj->limit - dmaobj->start;
	int ret;

	if (!nv_iclass(parent, NV_ENGCTX_CLASS)) {
		switch (nv_mclass(parent->parent)) {
		case NV03_CHANNEL_DMA_CLASS:
		case NV10_CHANNEL_DMA_CLASS:
		case NV17_CHANNEL_DMA_CLASS:
		case NV40_CHANNEL_DMA_CLASS:
			break;
		default:
			return -EINVAL;
		}
	}

	if (dmaobj->target == NV_MEM_TARGET_VM) {
		if (nv_object(vmm)->oclass == &nv04_vmmgr_oclass) {
			struct nouveau_gpuobj *pgt = vmm->vm->pgt[0].obj[0];
			if (!dmaobj->start)
				return nouveau_gpuobj_dup(parent, pgt, pgpuobj);
			offset  = nv_ro32(pgt, 8 + (offset >> 10));
			offset &= 0xfffff000;
		}

		dmaobj->target = NV_MEM_TARGET_PCI;
		dmaobj->access = NV_MEM_ACCESS_RW;
	}

	switch (dmaobj->target) {
	case NV_MEM_TARGET_VRAM:
		flags0 |= 0x00003000;
		break;
	case NV_MEM_TARGET_PCI:
		flags0 |= 0x00023000;
		break;
	case NV_MEM_TARGET_PCI_NOSNOOP:
		flags0 |= 0x00033000;
		break;
	default:
		return -EINVAL;
	}

	switch (dmaobj->access) {
	case NV_MEM_ACCESS_RO:
		flags0 |= 0x00004000;
		break;
	case NV_MEM_ACCESS_WO:
		flags0 |= 0x00008000;
	case NV_MEM_ACCESS_RW:
		flags2 |= 0x00000002;
		break;
	default:
		return -EINVAL;
	}

	ret = nouveau_gpuobj_new(parent, parent, 16, 16, 0, &gpuobj);
	*pgpuobj = gpuobj;
	if (ret == 0) {
		nv_wo32(*pgpuobj, 0x00, flags0 | (adjust << 20));
		nv_wo32(*pgpuobj, 0x04, length);
		nv_wo32(*pgpuobj, 0x08, flags2 | offset);
		nv_wo32(*pgpuobj, 0x0c, flags2 | offset);
	}

	return ret;
}

static int
nv04_dmaeng_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		 struct nouveau_oclass *oclass, void *data, u32 size,
		 struct nouveau_object **pobject)
{
	struct nv04_dmaeng_priv *priv;
	int ret;

	ret = nouveau_dmaeng_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_engine(priv)->sclass = nouveau_dmaobj_sclass;
	priv->base.bind = nv04_dmaobj_bind;
	return 0;
}

struct nouveau_oclass
nv04_dmaeng_oclass = {
	.handle = NV_ENGINE(DMAOBJ, 0x04),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv04_dmaeng_ctor,
		.dtor = _nouveau_dmaeng_dtor,
		.init = _nouveau_dmaeng_init,
		.fini = _nouveau_dmaeng_fini,
	},
};

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
#include <core/gpuobj.h>
#include <core/class.h>

#include <subdev/fb.h>
#include <engine/dmaobj.h>

struct nvd0_dmaeng_priv {
	struct nouveau_dmaeng base;
};

static int
nvd0_dmaobj_bind(struct nouveau_dmaeng *dmaeng,
		 struct nouveau_object *parent,
		 struct nouveau_dmaobj *dmaobj,
		 struct nouveau_gpuobj **pgpuobj)
{
	u32 flags0 = 0x00000000;
	int ret;

	if (!nv_iclass(parent, NV_ENGCTX_CLASS)) {
		switch (nv_mclass(parent->parent)) {
		case NVD0_DISP_MAST_CLASS:
		case NVD0_DISP_SYNC_CLASS:
		case NVD0_DISP_OVLY_CLASS:
		case NVE0_DISP_MAST_CLASS:
		case NVE0_DISP_SYNC_CLASS:
		case NVE0_DISP_OVLY_CLASS:
			break;
		default:
			return -EINVAL;
		}
	} else
		return 0;

	if (!(dmaobj->conf0 & NVD0_DMA_CONF0_ENABLE)) {
		if (dmaobj->target == NV_MEM_TARGET_VM) {
			dmaobj->conf0 |= NVD0_DMA_CONF0_TYPE_VM;
			dmaobj->conf0 |= NVD0_DMA_CONF0_PAGE_LP;
		} else {
			dmaobj->conf0 |= NVD0_DMA_CONF0_TYPE_LINEAR;
			dmaobj->conf0 |= NVD0_DMA_CONF0_PAGE_SP;
		}
	}

	flags0 |= (dmaobj->conf0 & NVD0_DMA_CONF0_TYPE) << 20;
	flags0 |= (dmaobj->conf0 & NVD0_DMA_CONF0_PAGE) >> 4;

	switch (dmaobj->target) {
	case NV_MEM_TARGET_VRAM:
		flags0 |= 0x00000009;
		break;
	default:
		return -EINVAL;
		break;
	}

	ret = nouveau_gpuobj_new(parent, parent, 24, 32, 0, pgpuobj);
	if (ret == 0) {
		nv_wo32(*pgpuobj, 0x00, flags0);
		nv_wo32(*pgpuobj, 0x04, dmaobj->start >> 8);
		nv_wo32(*pgpuobj, 0x08, dmaobj->limit >> 8);
		nv_wo32(*pgpuobj, 0x0c, 0x00000000);
		nv_wo32(*pgpuobj, 0x10, 0x00000000);
		nv_wo32(*pgpuobj, 0x14, 0x00000000);
	}

	return ret;
}

static int
nvd0_dmaeng_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		 struct nouveau_oclass *oclass, void *data, u32 size,
		 struct nouveau_object **pobject)
{
	struct nvd0_dmaeng_priv *priv;
	int ret;

	ret = nouveau_dmaeng_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_engine(priv)->sclass = nouveau_dmaobj_sclass;
	priv->base.bind = nvd0_dmaobj_bind;
	return 0;
}

struct nouveau_oclass
nvd0_dmaeng_oclass = {
	.handle = NV_ENGINE(DMAOBJ, 0xd0),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nvd0_dmaeng_ctor,
		.dtor = _nouveau_dmaeng_dtor,
		.init = _nouveau_dmaeng_init,
		.fini = _nouveau_dmaeng_fini,
	},
};

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
#include <core/os.h>
#include <core/class.h>
#include <core/engctx.h>

#include <engine/software.h>
#include <engine/disp.h>

struct nvc0_software_priv {
	struct nouveau_software base;
};

struct nvc0_software_chan {
	struct nouveau_software_chan base;
};

/*******************************************************************************
 * software object classes
 ******************************************************************************/

static int
nvc0_software_mthd_vblsem_offset(struct nouveau_object *object, u32 mthd,
				 void *args, u32 size)
{
	struct nvc0_software_chan *chan = (void *)nv_engctx(object->parent);
	u64 data = *(u32 *)args;
	if (mthd == 0x0400) {
		chan->base.vblank.offset &= 0x00ffffffffULL;
		chan->base.vblank.offset |= data << 32;
	} else {
		chan->base.vblank.offset &= 0xff00000000ULL;
		chan->base.vblank.offset |= data;
	}
	return 0;
}

static int
nvc0_software_mthd_vblsem_value(struct nouveau_object *object, u32 mthd,
				void *args, u32 size)
{
	struct nvc0_software_chan *chan = (void *)nv_engctx(object->parent);
	chan->base.vblank.value = *(u32 *)args;
	return 0;
}

static int
nvc0_software_mthd_vblsem_release(struct nouveau_object *object, u32 mthd,
				  void *args, u32 size)
{
	struct nvc0_software_chan *chan = (void *)nv_engctx(object->parent);
	struct nouveau_disp *disp = nouveau_disp(object);
	unsigned long flags;
	u32 crtc = *(u32 *)args;

	if ((nv_device(object)->card_type < NV_E0 && crtc > 1) || crtc > 3)
		return -EINVAL;

	disp->vblank.get(disp->vblank.data, crtc);

	spin_lock_irqsave(&disp->vblank.lock, flags);
	list_add(&chan->base.vblank.head, &disp->vblank.list);
	chan->base.vblank.crtc = crtc;
	spin_unlock_irqrestore(&disp->vblank.lock, flags);
	return 0;
}

static int
nvc0_software_mthd_flip(struct nouveau_object *object, u32 mthd,
			void *args, u32 size)
{
	struct nvc0_software_chan *chan = (void *)nv_engctx(object->parent);
	if (chan->base.flip)
		return chan->base.flip(chan->base.flip_data);
	return -EINVAL;
}

static struct nouveau_omthds
nvc0_software_omthds[] = {
	{ 0x0400, 0x0400, nvc0_software_mthd_vblsem_offset },
	{ 0x0404, 0x0404, nvc0_software_mthd_vblsem_offset },
	{ 0x0408, 0x0408, nvc0_software_mthd_vblsem_value },
	{ 0x040c, 0x040c, nvc0_software_mthd_vblsem_release },
	{ 0x0500, 0x0500, nvc0_software_mthd_flip },
	{}
};

static struct nouveau_oclass
nvc0_software_sclass[] = {
	{ 0x906e, &nouveau_object_ofuncs, nvc0_software_omthds },
	{}
};

/*******************************************************************************
 * software context
 ******************************************************************************/

static int
nvc0_software_context_ctor(struct nouveau_object *parent,
			   struct nouveau_object *engine,
			   struct nouveau_oclass *oclass, void *data, u32 size,
			   struct nouveau_object **pobject)
{
	struct nvc0_software_chan *chan;
	int ret;

	ret = nouveau_software_context_create(parent, engine, oclass, &chan);
	*pobject = nv_object(chan);
	if (ret)
		return ret;

	chan->base.vblank.channel = nv_gpuobj(parent->parent)->addr >> 12;
	return 0;
}

static struct nouveau_oclass
nvc0_software_cclass = {
	.handle = NV_ENGCTX(SW, 0xc0),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nvc0_software_context_ctor,
		.dtor = _nouveau_software_context_dtor,
		.init = _nouveau_software_context_init,
		.fini = _nouveau_software_context_fini,
	},
};

/*******************************************************************************
 * software engine/subdev functions
 ******************************************************************************/

static int
nvc0_software_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		   struct nouveau_oclass *oclass, void *data, u32 size,
		   struct nouveau_object **pobject)
{
	struct nvc0_software_priv *priv;
	int ret;

	ret = nouveau_software_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_engine(priv)->cclass = &nvc0_software_cclass;
	nv_engine(priv)->sclass = nvc0_software_sclass;
	nv_subdev(priv)->intr = nv04_software_intr;
	return 0;
}

struct nouveau_oclass
nvc0_software_oclass = {
	.handle = NV_ENGINE(SW, 0xc0),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nvc0_software_ctor,
		.dtor = _nouveau_software_dtor,
		.init = _nouveau_software_init,
		.fini = _nouveau_software_fini,
	},
};

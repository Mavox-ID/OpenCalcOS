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
#include <engine/fifo.h>

struct nv04_software_priv {
	struct nouveau_software base;
};

struct nv04_software_chan {
	struct nouveau_software_chan base;
};

/*******************************************************************************
 * software object classes
 ******************************************************************************/

static int
nv04_software_set_ref(struct nouveau_object *object, u32 mthd,
		      void *data, u32 size)
{
	struct nouveau_object *channel = (void *)nv_engctx(object->parent);
	struct nouveau_fifo_chan *fifo = (void *)channel->parent;
	atomic_set(&fifo->refcnt, *(u32*)data);
	return 0;
}

static int
nv04_software_flip(struct nouveau_object *object, u32 mthd,
		   void *args, u32 size)
{
	struct nv04_software_chan *chan = (void *)nv_engctx(object->parent);
	if (chan->base.flip)
		return chan->base.flip(chan->base.flip_data);
	return -EINVAL;
}

static struct nouveau_omthds
nv04_software_omthds[] = {
	{ 0x0150, 0x0150, nv04_software_set_ref },
	{ 0x0500, 0x0500, nv04_software_flip },
	{}
};

static struct nouveau_oclass
nv04_software_sclass[] = {
	{ 0x006e, &nouveau_object_ofuncs, nv04_software_omthds },
	{}
};

/*******************************************************************************
 * software context
 ******************************************************************************/

static int
nv04_software_context_ctor(struct nouveau_object *parent,
		      struct nouveau_object *engine,
		      struct nouveau_oclass *oclass, void *data, u32 size,
		      struct nouveau_object **pobject)
{
	struct nv04_software_chan *chan;
	int ret;

	ret = nouveau_software_context_create(parent, engine, oclass, &chan);
	*pobject = nv_object(chan);
	if (ret)
		return ret;

	return 0;
}

static struct nouveau_oclass
nv04_software_cclass = {
	.handle = NV_ENGCTX(SW, 0x04),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv04_software_context_ctor,
		.dtor = _nouveau_software_context_dtor,
		.init = _nouveau_software_context_init,
		.fini = _nouveau_software_context_fini,
	},
};

/*******************************************************************************
 * software engine/subdev functions
 ******************************************************************************/

void
nv04_software_intr(struct nouveau_subdev *subdev)
{
	nv_mask(subdev, 0x000100, 0x80000000, 0x00000000);
}

static int
nv04_software_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	      struct nouveau_oclass *oclass, void *data, u32 size,
	      struct nouveau_object **pobject)
{
	struct nv04_software_priv *priv;
	int ret;

	ret = nouveau_software_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_engine(priv)->cclass = &nv04_software_cclass;
	nv_engine(priv)->sclass = nv04_software_sclass;
	nv_subdev(priv)->intr = nv04_software_intr;
	return 0;
}

struct nouveau_oclass
nv04_software_oclass = {
	.handle = NV_ENGINE(SW, 0x04),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv04_software_ctor,
		.dtor = _nouveau_software_dtor,
		.init = _nouveau_software_init,
		.fini = _nouveau_software_fini,
	},
};

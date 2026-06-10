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
#include <core/falcon.h>
#include <core/class.h>
#include <core/enum.h>

#include <engine/fifo.h>
#include <engine/copy.h>

#include "fuc/nvc0.fuc.h"

struct nvc0_copy_priv {
	struct nouveau_falcon base;
};

/*******************************************************************************
 * Copy object classes
 ******************************************************************************/

static struct nouveau_oclass
nvc0_copy0_sclass[] = {
	{ 0x90b5, &nouveau_object_ofuncs },
	{},
};

static struct nouveau_oclass
nvc0_copy1_sclass[] = {
	{ 0x90b8, &nouveau_object_ofuncs },
	{},
};

/*******************************************************************************
 * PCOPY context
 ******************************************************************************/

static struct nouveau_ofuncs
nvc0_copy_context_ofuncs = {
	.ctor = _nouveau_falcon_context_ctor,
	.dtor = _nouveau_falcon_context_dtor,
	.init = _nouveau_falcon_context_init,
	.fini = _nouveau_falcon_context_fini,
	.rd32 = _nouveau_falcon_context_rd32,
	.wr32 = _nouveau_falcon_context_wr32,
};

static struct nouveau_oclass
nvc0_copy0_cclass = {
	.handle = NV_ENGCTX(COPY0, 0xc0),
	.ofuncs = &nvc0_copy_context_ofuncs,
};

static struct nouveau_oclass
nvc0_copy1_cclass = {
	.handle = NV_ENGCTX(COPY1, 0xc0),
	.ofuncs = &nvc0_copy_context_ofuncs,
};

/*******************************************************************************
 * PCOPY engine/subdev functions
 ******************************************************************************/

static int
nvc0_copy_init(struct nouveau_object *object)
{
	struct nvc0_copy_priv *priv = (void *)object;
	int ret;

	ret = nouveau_falcon_init(&priv->base);
	if (ret)
		return ret;

	nv_wo32(priv, 0x084, nv_engidx(object) - NVDEV_ENGINE_COPY0);
	return 0;
}

static int
nvc0_copy0_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		struct nouveau_oclass *oclass, void *data, u32 size,
		struct nouveau_object **pobject)
{
	struct nvc0_copy_priv *priv;
	int ret;

	if (nv_rd32(parent, 0x022500) & 0x00000100)
		return -ENODEV;

	ret = nouveau_falcon_create(parent, engine, oclass, 0x104000, true,
				    "PCE0", "copy0", &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->unit = 0x00000040;
	nv_subdev(priv)->intr = nva3_copy_intr;
	nv_engine(priv)->cclass = &nvc0_copy0_cclass;
	nv_engine(priv)->sclass = nvc0_copy0_sclass;
	nv_falcon(priv)->code.data = nvc0_pcopy_code;
	nv_falcon(priv)->code.size = sizeof(nvc0_pcopy_code);
	nv_falcon(priv)->data.data = nvc0_pcopy_data;
	nv_falcon(priv)->data.size = sizeof(nvc0_pcopy_data);
	return 0;
}

static int
nvc0_copy1_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		struct nouveau_oclass *oclass, void *data, u32 size,
		struct nouveau_object **pobject)
{
	struct nvc0_copy_priv *priv;
	int ret;

	if (nv_rd32(parent, 0x022500) & 0x00000200)
		return -ENODEV;

	ret = nouveau_falcon_create(parent, engine, oclass, 0x105000, true,
				    "PCE1", "copy1", &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->unit = 0x00000080;
	nv_subdev(priv)->intr = nva3_copy_intr;
	nv_engine(priv)->cclass = &nvc0_copy1_cclass;
	nv_engine(priv)->sclass = nvc0_copy1_sclass;
	nv_falcon(priv)->code.data = nvc0_pcopy_code;
	nv_falcon(priv)->code.size = sizeof(nvc0_pcopy_code);
	nv_falcon(priv)->data.data = nvc0_pcopy_data;
	nv_falcon(priv)->data.size = sizeof(nvc0_pcopy_data);
	return 0;
}

struct nouveau_oclass
nvc0_copy0_oclass = {
	.handle = NV_ENGINE(COPY0, 0xc0),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nvc0_copy0_ctor,
		.dtor = _nouveau_falcon_dtor,
		.init = nvc0_copy_init,
		.fini = _nouveau_falcon_fini,
		.rd32 = _nouveau_falcon_rd32,
		.wr32 = _nouveau_falcon_wr32,
	},
};

struct nouveau_oclass
nvc0_copy1_oclass = {
	.handle = NV_ENGINE(COPY1, 0xc0),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nvc0_copy1_ctor,
		.dtor = _nouveau_falcon_dtor,
		.init = nvc0_copy_init,
		.fini = _nouveau_falcon_fini,
		.rd32 = _nouveau_falcon_rd32,
		.wr32 = _nouveau_falcon_wr32,
	},
};

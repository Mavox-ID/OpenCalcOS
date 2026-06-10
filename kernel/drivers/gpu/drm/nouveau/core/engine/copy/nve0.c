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
#include <core/enum.h>
#include <core/class.h>
#include <core/engctx.h>

#include <engine/copy.h>

struct nve0_copy_priv {
	struct nouveau_engine base;
};

/*******************************************************************************
 * Copy object classes
 ******************************************************************************/

static struct nouveau_oclass
nve0_copy_sclass[] = {
	{ 0xa0b5, &nouveau_object_ofuncs },
	{},
};

/*******************************************************************************
 * PCOPY context
 ******************************************************************************/

static struct nouveau_ofuncs
nve0_copy_context_ofuncs = {
	.ctor = _nouveau_engctx_ctor,
	.dtor = _nouveau_engctx_dtor,
	.init = _nouveau_engctx_init,
	.fini = _nouveau_engctx_fini,
	.rd32 = _nouveau_engctx_rd32,
	.wr32 = _nouveau_engctx_wr32,
};

static struct nouveau_oclass
nve0_copy_cclass = {
	.handle = NV_ENGCTX(COPY0, 0xc0),
	.ofuncs = &nve0_copy_context_ofuncs,
};

/*******************************************************************************
 * PCOPY engine/subdev functions
 ******************************************************************************/

static int
nve0_copy0_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		struct nouveau_oclass *oclass, void *data, u32 size,
		struct nouveau_object **pobject)
{
	struct nve0_copy_priv *priv;
	int ret;

	if (nv_rd32(parent, 0x022500) & 0x00000100)
		return -ENODEV;

	ret = nouveau_engine_create(parent, engine, oclass, true,
				    "PCE0", "copy0", &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->unit = 0x00000040;
	nv_engine(priv)->cclass = &nve0_copy_cclass;
	nv_engine(priv)->sclass = nve0_copy_sclass;
	return 0;
}

static int
nve0_copy1_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		struct nouveau_oclass *oclass, void *data, u32 size,
		struct nouveau_object **pobject)
{
	struct nve0_copy_priv *priv;
	int ret;

	if (nv_rd32(parent, 0x022500) & 0x00000200)
		return -ENODEV;

	ret = nouveau_engine_create(parent, engine, oclass, true,
				    "PCE1", "copy1", &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->unit = 0x00000080;
	nv_engine(priv)->cclass = &nve0_copy_cclass;
	nv_engine(priv)->sclass = nve0_copy_sclass;
	return 0;
}

struct nouveau_oclass
nve0_copy0_oclass = {
	.handle = NV_ENGINE(COPY0, 0xe0),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nve0_copy0_ctor,
		.dtor = _nouveau_engine_dtor,
		.init = _nouveau_engine_init,
		.fini = _nouveau_engine_fini,
	},
};

struct nouveau_oclass
nve0_copy1_oclass = {
	.handle = NV_ENGINE(COPY1, 0xe0),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nve0_copy1_ctor,
		.dtor = _nouveau_engine_dtor,
		.init = _nouveau_engine_init,
		.fini = _nouveau_engine_fini,
	},
};

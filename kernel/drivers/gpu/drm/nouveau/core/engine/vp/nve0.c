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

#include <engine/vp.h>

struct nve0_vp_priv {
	struct nouveau_falcon base;
};

/*******************************************************************************
 * VP object classes
 ******************************************************************************/

static struct nouveau_oclass
nve0_vp_sclass[] = {
	{ 0x95b2, &nouveau_object_ofuncs },
	{},
};

/*******************************************************************************
 * PVP context
 ******************************************************************************/

static struct nouveau_oclass
nve0_vp_cclass = {
	.handle = NV_ENGCTX(VP, 0xe0),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = _nouveau_falcon_context_ctor,
		.dtor = _nouveau_falcon_context_dtor,
		.init = _nouveau_falcon_context_init,
		.fini = _nouveau_falcon_context_fini,
		.rd32 = _nouveau_falcon_context_rd32,
		.wr32 = _nouveau_falcon_context_wr32,
	},
};

/*******************************************************************************
 * PVP engine/subdev functions
 ******************************************************************************/

static int
nve0_vp_init(struct nouveau_object *object)
{
	struct nve0_vp_priv *priv = (void *)object;
	int ret;

	ret = nouveau_falcon_init(&priv->base);
	if (ret)
		return ret;

	nv_wr32(priv, 0x085010, 0x0000fff2);
	nv_wr32(priv, 0x08501c, 0x0000fff2);
	return 0;
}

static int
nve0_vp_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	     struct nouveau_oclass *oclass, void *data, u32 size,
	     struct nouveau_object **pobject)
{
	struct nve0_vp_priv *priv;
	int ret;

	ret = nouveau_falcon_create(parent, engine, oclass, 0x085000, true,
				    "PVP", "vp", &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->unit = 0x00020000;
	nv_engine(priv)->cclass = &nve0_vp_cclass;
	nv_engine(priv)->sclass = nve0_vp_sclass;
	return 0;
}

struct nouveau_oclass
nve0_vp_oclass = {
	.handle = NV_ENGINE(VP, 0xe0),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nve0_vp_ctor,
		.dtor = _nouveau_falcon_dtor,
		.init = nve0_vp_init,
		.fini = _nouveau_falcon_fini,
		.rd32 = _nouveau_falcon_rd32,
		.wr32 = _nouveau_falcon_wr32,
	},
};

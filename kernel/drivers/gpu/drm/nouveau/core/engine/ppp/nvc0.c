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

#include <engine/ppp.h>

struct nvc0_ppp_priv {
	struct nouveau_falcon base;
};

/*******************************************************************************
 * PPP object classes
 ******************************************************************************/

static struct nouveau_oclass
nvc0_ppp_sclass[] = {
	{ 0x90b3, &nouveau_object_ofuncs },
	{},
};

/*******************************************************************************
 * PPPP context
 ******************************************************************************/

static struct nouveau_oclass
nvc0_ppp_cclass = {
	.handle = NV_ENGCTX(PPP, 0xc0),
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
 * PPPP engine/subdev functions
 ******************************************************************************/

static int
nvc0_ppp_init(struct nouveau_object *object)
{
	struct nvc0_ppp_priv *priv = (void *)object;
	int ret;

	ret = nouveau_falcon_init(&priv->base);
	if (ret)
		return ret;

	nv_wr32(priv, 0x086010, 0x0000fff2);
	nv_wr32(priv, 0x08601c, 0x0000fff2);
	return 0;
}

static int
nvc0_ppp_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	      struct nouveau_oclass *oclass, void *data, u32 size,
	      struct nouveau_object **pobject)
{
	struct nvc0_ppp_priv *priv;
	int ret;

	ret = nouveau_falcon_create(parent, engine, oclass, 0x086000, true,
				    "PPPP", "ppp", &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->unit = 0x00000002;
	nv_engine(priv)->cclass = &nvc0_ppp_cclass;
	nv_engine(priv)->sclass = nvc0_ppp_sclass;
	return 0;
}

struct nouveau_oclass
nvc0_ppp_oclass = {
	.handle = NV_ENGINE(PPP, 0xc0),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nvc0_ppp_ctor,
		.dtor = _nouveau_falcon_dtor,
		.init = nvc0_ppp_init,
		.fini = _nouveau_falcon_fini,
		.rd32 = _nouveau_falcon_rd32,
		.wr32 = _nouveau_falcon_wr32,
	},
};

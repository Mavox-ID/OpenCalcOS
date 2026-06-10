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
#include <core/engctx.h>
#include <core/class.h>

#include <engine/vp.h>

struct nv84_vp_priv {
	struct nouveau_engine base;
};

/*******************************************************************************
 * VP object classes
 ******************************************************************************/

static struct nouveau_oclass
nv84_vp_sclass[] = {
	{},
};

/*******************************************************************************
 * PVP context
 ******************************************************************************/

static struct nouveau_oclass
nv84_vp_cclass = {
	.handle = NV_ENGCTX(VP, 0x84),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = _nouveau_engctx_ctor,
		.dtor = _nouveau_engctx_dtor,
		.init = _nouveau_engctx_init,
		.fini = _nouveau_engctx_fini,
		.rd32 = _nouveau_engctx_rd32,
		.wr32 = _nouveau_engctx_wr32,
	},
};

/*******************************************************************************
 * PVP engine/subdev functions
 ******************************************************************************/

static int
nv84_vp_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	     struct nouveau_oclass *oclass, void *data, u32 size,
	     struct nouveau_object **pobject)
{
	struct nv84_vp_priv *priv;
	int ret;

	ret = nouveau_engine_create(parent, engine, oclass, true,
				    "PVP", "vp", &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->unit = 0x01020000;
	nv_engine(priv)->cclass = &nv84_vp_cclass;
	nv_engine(priv)->sclass = nv84_vp_sclass;
	return 0;
}

struct nouveau_oclass
nv84_vp_oclass = {
	.handle = NV_ENGINE(VP, 0x84),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv84_vp_ctor,
		.dtor = _nouveau_engine_dtor,
		.init = _nouveau_engine_init,
		.fini = _nouveau_engine_fini,
	},
};

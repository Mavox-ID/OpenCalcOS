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
#include <core/engine.h>
#include <core/engctx.h>
#include <core/class.h>

#include <engine/ppp.h>

struct nv98_ppp_priv {
	struct nouveau_engine base;
};

struct nv98_ppp_chan {
	struct nouveau_engctx base;
};

/*******************************************************************************
 * PPP object classes
 ******************************************************************************/

static struct nouveau_oclass
nv98_ppp_sclass[] = {
	{},
};

/*******************************************************************************
 * PPPP context
 ******************************************************************************/

static struct nouveau_oclass
nv98_ppp_cclass = {
	.handle = NV_ENGCTX(PPP, 0x98),
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
 * PPPP engine/subdev functions
 ******************************************************************************/

static int
nv98_ppp_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	      struct nouveau_oclass *oclass, void *data, u32 size,
	      struct nouveau_object **pobject)
{
	struct nv98_ppp_priv *priv;
	int ret;

	ret = nouveau_engine_create(parent, engine, oclass, true,
				    "PPPP", "ppp", &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->unit = 0x00400002;
	nv_engine(priv)->cclass = &nv98_ppp_cclass;
	nv_engine(priv)->sclass = nv98_ppp_sclass;
	return 0;
}

struct nouveau_oclass
nv98_ppp_oclass = {
	.handle = NV_ENGINE(PPP, 0x98),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv98_ppp_ctor,
		.dtor = _nouveau_engine_dtor,
		.init = _nouveau_engine_init,
		.fini = _nouveau_engine_fini,
	},
};

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
#include <subdev/mc.h>

struct nv44_mc_priv {
	struct nouveau_mc base;
};

static int
nv44_mc_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	     struct nouveau_oclass *oclass, void *data, u32 size,
	     struct nouveau_object **pobject)
{
	struct nv44_mc_priv *priv;
	int ret;

	ret = nouveau_mc_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->intr = nouveau_mc_intr;
	priv->base.intr_map = nv04_mc_intr;
	return 0;
}

static int
nv44_mc_init(struct nouveau_object *object)
{
	struct nv44_mc_priv *priv = (void *)object;
	u32 tmp = nv_rd32(priv, 0x10020c);

	nv_wr32(priv, 0x000200, 0xffffffff); /* everything enabled */

	nv_wr32(priv, 0x001700, tmp);
	nv_wr32(priv, 0x001704, 0);
	nv_wr32(priv, 0x001708, 0);
	nv_wr32(priv, 0x00170c, tmp);

	return nouveau_mc_init(&priv->base);
}

struct nouveau_oclass
nv44_mc_oclass = {
	.handle = NV_SUBDEV(MC, 0x44),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv44_mc_ctor,
		.dtor = _nouveau_mc_dtor,
		.init = nv44_mc_init,
		.fini = _nouveau_mc_fini,
	},
};

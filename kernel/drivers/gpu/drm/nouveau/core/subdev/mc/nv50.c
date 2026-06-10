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

struct nv50_mc_priv {
	struct nouveau_mc base;
};

static const struct nouveau_mc_intr
nv50_mc_intr[] = {
	{ 0x00000001, NVDEV_ENGINE_MPEG },
	{ 0x00000100, NVDEV_ENGINE_FIFO },
	{ 0x00001000, NVDEV_ENGINE_GR },
	{ 0x00004000, NVDEV_ENGINE_CRYPT },	/* NV84- */
	{ 0x00008000, NVDEV_ENGINE_BSP },	/* NV84- */
	{ 0x00100000, NVDEV_SUBDEV_TIMER },
	{ 0x00200000, NVDEV_SUBDEV_GPIO },
	{ 0x04000000, NVDEV_ENGINE_DISP },
	{ 0x80000000, NVDEV_ENGINE_SW },
	{ 0x0000d101, NVDEV_SUBDEV_FB },
	{},
};

static int
nv50_mc_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	     struct nouveau_oclass *oclass, void *data, u32 size,
	     struct nouveau_object **pobject)
{
	struct nv50_mc_priv *priv;
	int ret;

	ret = nouveau_mc_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->intr = nouveau_mc_intr;
	priv->base.intr_map = nv50_mc_intr;
	return 0;
}

int
nv50_mc_init(struct nouveau_object *object)
{
	struct nv50_mc_priv *priv = (void *)object;
	nv_wr32(priv, 0x000200, 0xffffffff); /* everything on */
	return nouveau_mc_init(&priv->base);
}

struct nouveau_oclass
nv50_mc_oclass = {
	.handle = NV_SUBDEV(MC, 0x50),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv50_mc_ctor,
		.dtor = _nouveau_mc_dtor,
		.init = nv50_mc_init,
		.fini = _nouveau_mc_fini,
	},
};

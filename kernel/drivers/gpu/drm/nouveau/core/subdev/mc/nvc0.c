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

struct nvc0_mc_priv {
	struct nouveau_mc base;
};

static const struct nouveau_mc_intr
nvc0_mc_intr[] = {
	{ 0x00000001, NVDEV_ENGINE_PPP },
	{ 0x00000020, NVDEV_ENGINE_COPY0 },
	{ 0x00000040, NVDEV_ENGINE_COPY1 },
	{ 0x00000100, NVDEV_ENGINE_FIFO },
	{ 0x00001000, NVDEV_ENGINE_GR },
	{ 0x00008000, NVDEV_ENGINE_BSP },
	{ 0x00020000, NVDEV_ENGINE_VP },
	{ 0x00100000, NVDEV_SUBDEV_TIMER },
	{ 0x00200000, NVDEV_SUBDEV_GPIO },
	{ 0x02000000, NVDEV_SUBDEV_LTCG },
	{ 0x04000000, NVDEV_ENGINE_DISP },
	{ 0x40000000, NVDEV_SUBDEV_IBUS },
	{ 0x80000000, NVDEV_ENGINE_SW },
	{},
};

static int
nvc0_mc_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	     struct nouveau_oclass *oclass, void *data, u32 size,
	     struct nouveau_object **pobject)
{
	struct nvc0_mc_priv *priv;
	int ret;

	ret = nouveau_mc_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->intr = nouveau_mc_intr;
	priv->base.intr_map = nvc0_mc_intr;
	return 0;
}

struct nouveau_oclass
nvc0_mc_oclass = {
	.handle = NV_SUBDEV(MC, 0xc0),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nvc0_mc_ctor,
		.dtor = _nouveau_mc_dtor,
		.init = nv50_mc_init,
		.fini = _nouveau_mc_fini,
	},
};

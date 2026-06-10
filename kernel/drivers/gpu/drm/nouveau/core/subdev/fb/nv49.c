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
#include <subdev/fb.h>

struct nv49_fb_priv {
	struct nouveau_fb base;
};

static int
nv49_fb_vram_init(struct nouveau_fb *pfb)
{
	u32 pfb914 = nv_rd32(pfb, 0x100914);

	switch (pfb914 & 0x00000003) {
	case 0x00000000: pfb->ram.type = NV_MEM_TYPE_DDR1; break;
	case 0x00000001: pfb->ram.type = NV_MEM_TYPE_DDR2; break;
	case 0x00000002: pfb->ram.type = NV_MEM_TYPE_GDDR3; break;
	case 0x00000003: break;
	}

	pfb->ram.size =   nv_rd32(pfb, 0x10020c) & 0xff000000;
	pfb->ram.parts = (nv_rd32(pfb, 0x100200) & 0x00000003) + 1;
	return nv_rd32(pfb, 0x100320);
}

static int
nv49_fb_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	     struct nouveau_oclass *oclass, void *data, u32 size,
	     struct nouveau_object **pobject)
{
	struct nv49_fb_priv *priv;
	int ret;

	ret = nouveau_fb_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.memtype_valid = nv04_fb_memtype_valid;
	priv->base.ram.init = nv49_fb_vram_init;
	priv->base.tile.regions = 15;
	priv->base.tile.init = nv30_fb_tile_init;
	priv->base.tile.comp = nv40_fb_tile_comp;
	priv->base.tile.fini = nv20_fb_tile_fini;
	priv->base.tile.prog = nv41_fb_tile_prog;

	return nouveau_fb_preinit(&priv->base);
}


struct nouveau_oclass
nv49_fb_oclass = {
	.handle = NV_SUBDEV(FB, 0x49),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv49_fb_ctor,
		.dtor = _nouveau_fb_dtor,
		.init = nv41_fb_init,
		.fini = _nouveau_fb_fini,
	},
};

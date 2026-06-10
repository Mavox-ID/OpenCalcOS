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

struct nv40_fb_priv {
	struct nouveau_fb base;
};

static int
nv40_fb_vram_init(struct nouveau_fb *pfb)
{
	u32 pbus1218 = nv_rd32(pfb, 0x001218);
	switch (pbus1218 & 0x00000300) {
	case 0x00000000: pfb->ram.type = NV_MEM_TYPE_SDRAM; break;
	case 0x00000100: pfb->ram.type = NV_MEM_TYPE_DDR1; break;
	case 0x00000200: pfb->ram.type = NV_MEM_TYPE_GDDR3; break;
	case 0x00000300: pfb->ram.type = NV_MEM_TYPE_DDR2; break;
	}

	pfb->ram.size  =  nv_rd32(pfb, 0x10020c) & 0xff000000;
	pfb->ram.parts = (nv_rd32(pfb, 0x100200) & 0x00000003) + 1;
	return nv_rd32(pfb, 0x100320);
}

void
nv40_fb_tile_comp(struct nouveau_fb *pfb, int i, u32 size, u32 flags,
		  struct nouveau_fb_tile *tile)
{
	u32 tiles = DIV_ROUND_UP(size, 0x80);
	u32 tags  = round_up(tiles / pfb->ram.parts, 0x100);
	if ( (flags & 2) &&
	    !nouveau_mm_head(&pfb->tags, 1, tags, tags, 1, &tile->tag)) {
		tile->zcomp  = 0x28000000; /* Z24S8_SPLIT_GRAD */
		tile->zcomp |= ((tile->tag->offset           ) >> 8);
		tile->zcomp |= ((tile->tag->offset + tags - 1) >> 8) << 13;
#ifdef __BIG_ENDIAN
		tile->zcomp |= 0x40000000;
#endif
	}
}

static int
nv40_fb_init(struct nouveau_object *object)
{
	struct nv40_fb_priv *priv = (void *)object;
	int ret;

	ret = nouveau_fb_init(&priv->base);
	if (ret)
		return ret;

	nv_mask(priv, 0x10033c, 0x00008000, 0x00000000);
	return 0;
}

static int
nv40_fb_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	     struct nouveau_oclass *oclass, void *data, u32 size,
	     struct nouveau_object **pobject)
{
	struct nv40_fb_priv *priv;
	int ret;

	ret = nouveau_fb_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.memtype_valid = nv04_fb_memtype_valid;
	priv->base.ram.init = nv40_fb_vram_init;
	priv->base.tile.regions = 8;
	priv->base.tile.init = nv30_fb_tile_init;
	priv->base.tile.comp = nv40_fb_tile_comp;
	priv->base.tile.fini = nv20_fb_tile_fini;
	priv->base.tile.prog = nv20_fb_tile_prog;
	return nouveau_fb_preinit(&priv->base);
}


struct nouveau_oclass
nv40_fb_oclass = {
	.handle = NV_SUBDEV(FB, 0x40),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv40_fb_ctor,
		.dtor = _nouveau_fb_dtor,
		.init = nv40_fb_init,
		.fini = _nouveau_fb_fini,
	},
};

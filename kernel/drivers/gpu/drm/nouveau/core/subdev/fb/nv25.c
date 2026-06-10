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

struct nv25_fb_priv {
	struct nouveau_fb base;
};

static void
nv25_fb_tile_comp(struct nouveau_fb *pfb, int i, u32 size, u32 flags,
		  struct nouveau_fb_tile *tile)
{
	u32 tiles = DIV_ROUND_UP(size, 0x40);
	u32 tags  = round_up(tiles / pfb->ram.parts, 0x40);
	if (!nouveau_mm_head(&pfb->tags, 1, tags, tags, 1, &tile->tag)) {
		if (!(flags & 2)) tile->zcomp = 0x00100000; /* Z16 */
		else              tile->zcomp = 0x00200000; /* Z24S8 */
		tile->zcomp |= tile->tag->offset;
#ifdef __BIG_ENDIAN
		tile->zcomp |= 0x01000000;
#endif
	}
}

static int
nv25_fb_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	     struct nouveau_oclass *oclass, void *data, u32 size,
	     struct nouveau_object **pobject)
{
	struct nv25_fb_priv *priv;
	int ret;

	ret = nouveau_fb_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.memtype_valid = nv04_fb_memtype_valid;
	priv->base.ram.init = nv20_fb_vram_init;
	priv->base.tile.regions = 8;
	priv->base.tile.init = nv20_fb_tile_init;
	priv->base.tile.comp = nv25_fb_tile_comp;
	priv->base.tile.fini = nv20_fb_tile_fini;
	priv->base.tile.prog = nv20_fb_tile_prog;
	return nouveau_fb_preinit(&priv->base);
}

struct nouveau_oclass
nv25_fb_oclass = {
	.handle = NV_SUBDEV(FB, 0x25),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv25_fb_ctor,
		.dtor = _nouveau_fb_dtor,
		.init = _nouveau_fb_init,
		.fini = _nouveau_fb_fini,
	},
};

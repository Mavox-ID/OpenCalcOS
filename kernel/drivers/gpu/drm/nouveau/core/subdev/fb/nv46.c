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

struct nv46_fb_priv {
	struct nouveau_fb base;
};

void
nv46_fb_tile_init(struct nouveau_fb *pfb, int i, u32 addr, u32 size, u32 pitch,
		  u32 flags, struct nouveau_fb_tile *tile)
{
	/* for performance, select alternate bank offset for zeta */
	if (!(flags & 4)) tile->addr = (0 << 3);
	else              tile->addr = (1 << 3);

	tile->addr |= 0x00000001; /* mode = vram */
	tile->addr |= addr;
	tile->limit = max(1u, addr + size) - 1;
	tile->pitch = pitch;
}

static int
nv46_fb_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	     struct nouveau_oclass *oclass, void *data, u32 size,
	     struct nouveau_object **pobject)
{
	struct nv46_fb_priv *priv;
	int ret;

	ret = nouveau_fb_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.memtype_valid = nv04_fb_memtype_valid;
	priv->base.ram.init = nv44_fb_vram_init;
	priv->base.tile.regions = 15;
	priv->base.tile.init = nv46_fb_tile_init;
	priv->base.tile.fini = nv20_fb_tile_fini;
	priv->base.tile.prog = nv44_fb_tile_prog;
	return nouveau_fb_preinit(&priv->base);
}


struct nouveau_oclass
nv46_fb_oclass = {
	.handle = NV_SUBDEV(FB, 0x46),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv46_fb_ctor,
		.dtor = _nouveau_fb_dtor,
		.init = nv44_fb_init,
		.fini = _nouveau_fb_fini,
	},
};

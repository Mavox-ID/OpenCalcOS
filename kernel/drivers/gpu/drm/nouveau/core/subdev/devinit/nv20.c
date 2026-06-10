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
#include <subdev/devinit.h>
#include <subdev/vga.h>

#include "fbmem.h"

struct nv20_devinit_priv {
	struct nouveau_devinit base;
	u8 owner;
};

static void
nv20_devinit_meminit(struct nouveau_devinit *devinit)
{
	struct nv20_devinit_priv *priv = (void *)devinit;
	struct nouveau_device *device = nv_device(priv);
	uint32_t mask = (device->chipset >= 0x25 ? 0x300 : 0x900);
	uint32_t amount, off;
	struct io_mapping *fb;

	/* Map the framebuffer aperture */
	fb = fbmem_init(nv_device(priv)->pdev);
	if (!fb) {
		nv_error(priv, "failed to map fb\n");
		return;
	}

	nv_wr32(priv, NV10_PFB_REFCTRL, NV10_PFB_REFCTRL_VALID_1);

	/* Allow full addressing */
	nv_mask(priv, NV04_PFB_CFG0, 0, mask);

	amount = nv_rd32(priv, 0x10020c);
	for (off = amount; off > 0x2000000; off -= 0x2000000)
		fbmem_poke(fb, off - 4, off);

	amount = nv_rd32(priv, 0x10020c);
	if (amount != fbmem_peek(fb, amount - 4))
		/* IC missing - disable the upper half memory space. */
		nv_mask(priv, NV04_PFB_CFG0, mask, 0);

	fbmem_fini(fb);
}

static int
nv20_devinit_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		  struct nouveau_oclass *oclass, void *data, u32 size,
		  struct nouveau_object **pobject)
{
	struct nv20_devinit_priv *priv;
	int ret;

	ret = nouveau_devinit_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.meminit = nv20_devinit_meminit;
	return 0;
}

struct nouveau_oclass
nv20_devinit_oclass = {
	.handle = NV_SUBDEV(DEVINIT, 0x20),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv20_devinit_ctor,
		.dtor = nv04_devinit_dtor,
		.init = nv04_devinit_init,
		.fini = nv04_devinit_fini,
	},
};

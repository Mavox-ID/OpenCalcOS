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

struct nv10_devinit_priv {
	struct nouveau_devinit base;
	u8 owner;
};

static void
nv10_devinit_meminit(struct nouveau_devinit *devinit)
{
	struct nv10_devinit_priv *priv = (void *)devinit;
	const int mem_width[] = { 0x10, 0x00, 0x20 };
	const int mem_width_count = nv_device(priv)->chipset >= 0x17 ? 3 : 2;
	uint32_t patt = 0xdeadbeef;
	struct io_mapping *fb;
	int i, j, k;

	/* Map the framebuffer aperture */
	fb = fbmem_init(nv_device(priv)->pdev);
	if (!fb) {
		nv_error(priv, "failed to map fb\n");
		return;
	}

	nv_wr32(priv, NV10_PFB_REFCTRL, NV10_PFB_REFCTRL_VALID_1);

	/* Probe memory bus width */
	for (i = 0; i < mem_width_count; i++) {
		nv_mask(priv, NV04_PFB_CFG0, 0x30, mem_width[i]);

		for (j = 0; j < 4; j++) {
			for (k = 0; k < 4; k++)
				fbmem_poke(fb, 0x1c, 0);

			fbmem_poke(fb, 0x1c, patt);
			fbmem_poke(fb, 0x3c, 0);

			if (fbmem_peek(fb, 0x1c) == patt)
				goto mem_width_found;
		}
	}

mem_width_found:
	patt <<= 1;

	/* Probe amount of installed memory */
	for (i = 0; i < 4; i++) {
		int off = nv_rd32(priv, 0x10020c) - 0x100000;

		fbmem_poke(fb, off, patt);
		fbmem_poke(fb, 0, 0);

		fbmem_peek(fb, 0);
		fbmem_peek(fb, 0);
		fbmem_peek(fb, 0);
		fbmem_peek(fb, 0);

		if (fbmem_peek(fb, off) == patt)
			goto amount_found;
	}

	/* IC missing - disable the upper half memory space. */
	nv_mask(priv, NV04_PFB_CFG0, 0x1000, 0);

amount_found:
	fbmem_fini(fb);
}

static int
nv10_devinit_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		  struct nouveau_oclass *oclass, void *data, u32 size,
		  struct nouveau_object **pobject)
{
	struct nv10_devinit_priv *priv;
	int ret;

	ret = nouveau_devinit_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.meminit = nv10_devinit_meminit;
	return 0;
}

struct nouveau_oclass
nv10_devinit_oclass = {
	.handle = NV_SUBDEV(DEVINIT, 0x10),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv10_devinit_ctor,
		.dtor = nv04_devinit_dtor,
		.init = nv04_devinit_init,
		.fini = nv04_devinit_fini,
	},
};

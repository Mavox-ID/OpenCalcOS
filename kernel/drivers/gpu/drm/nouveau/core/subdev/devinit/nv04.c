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

struct nv04_devinit_priv {
	struct nouveau_devinit base;
	int owner;
};

static void
nv04_devinit_meminit(struct nouveau_devinit *devinit)
{
	struct nv04_devinit_priv *priv = (void *)devinit;
	u32 patt = 0xdeadbeef;
	struct io_mapping *fb;
	int i;

	/* Map the framebuffer aperture */
	fb = fbmem_init(nv_device(priv)->pdev);
	if (!fb) {
		nv_error(priv, "failed to map fb\n");
		return;
	}

	/* Sequencer and refresh off */
	nv_wrvgas(priv, 0, 1, nv_rdvgas(priv, 0, 1) | 0x20);
	nv_mask(priv, NV04_PFB_DEBUG_0, 0, NV04_PFB_DEBUG_0_REFRESH_OFF);

	nv_mask(priv, NV04_PFB_BOOT_0, ~0,
		      NV04_PFB_BOOT_0_RAM_AMOUNT_16MB |
		      NV04_PFB_BOOT_0_RAM_WIDTH_128 |
		      NV04_PFB_BOOT_0_RAM_TYPE_SGRAM_16MBIT);

	for (i = 0; i < 4; i++)
		fbmem_poke(fb, 4 * i, patt);

	fbmem_poke(fb, 0x400000, patt + 1);

	if (fbmem_peek(fb, 0) == patt + 1) {
		nv_mask(priv, NV04_PFB_BOOT_0,
			      NV04_PFB_BOOT_0_RAM_TYPE,
			      NV04_PFB_BOOT_0_RAM_TYPE_SDRAM_16MBIT);
		nv_mask(priv, NV04_PFB_DEBUG_0,
			      NV04_PFB_DEBUG_0_REFRESH_OFF, 0);

		for (i = 0; i < 4; i++)
			fbmem_poke(fb, 4 * i, patt);

		if ((fbmem_peek(fb, 0xc) & 0xffff) != (patt & 0xffff))
			nv_mask(priv, NV04_PFB_BOOT_0,
				      NV04_PFB_BOOT_0_RAM_WIDTH_128 |
				      NV04_PFB_BOOT_0_RAM_AMOUNT,
				      NV04_PFB_BOOT_0_RAM_AMOUNT_8MB);
	} else
	if ((fbmem_peek(fb, 0xc) & 0xffff0000) != (patt & 0xffff0000)) {
		nv_mask(priv, NV04_PFB_BOOT_0,
			      NV04_PFB_BOOT_0_RAM_WIDTH_128 |
			      NV04_PFB_BOOT_0_RAM_AMOUNT,
			      NV04_PFB_BOOT_0_RAM_AMOUNT_4MB);
	} else
	if (fbmem_peek(fb, 0) != patt) {
		if (fbmem_readback(fb, 0x800000, patt))
			nv_mask(priv, NV04_PFB_BOOT_0,
				      NV04_PFB_BOOT_0_RAM_AMOUNT,
				      NV04_PFB_BOOT_0_RAM_AMOUNT_8MB);
		else
			nv_mask(priv, NV04_PFB_BOOT_0,
				      NV04_PFB_BOOT_0_RAM_AMOUNT,
				      NV04_PFB_BOOT_0_RAM_AMOUNT_4MB);

		nv_mask(priv, NV04_PFB_BOOT_0, NV04_PFB_BOOT_0_RAM_TYPE,
			      NV04_PFB_BOOT_0_RAM_TYPE_SGRAM_8MBIT);
	} else
	if (!fbmem_readback(fb, 0x800000, patt)) {
		nv_mask(priv, NV04_PFB_BOOT_0, NV04_PFB_BOOT_0_RAM_AMOUNT,
			      NV04_PFB_BOOT_0_RAM_AMOUNT_8MB);

	}

	/* Refresh on, sequencer on */
	nv_mask(priv, NV04_PFB_DEBUG_0, NV04_PFB_DEBUG_0_REFRESH_OFF, 0);
	nv_wrvgas(priv, 0, 1, nv_rdvgas(priv, 0, 1) & ~0x20);
	fbmem_fini(fb);
}

static int
nv04_devinit_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		  struct nouveau_oclass *oclass, void *data, u32 size,
		  struct nouveau_object **pobject)
{
	struct nv04_devinit_priv *priv;
	int ret;

	ret = nouveau_devinit_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.meminit = nv04_devinit_meminit;
	priv->owner = -1;
	return 0;
}

void
nv04_devinit_dtor(struct nouveau_object *object)
{
	struct nv04_devinit_priv *priv = (void *)object;

	/* restore vga owner saved at first init, and lock crtc regs  */
	nv_wrvgaowner(priv, priv->owner);
	nv_lockvgac(priv, true);

	nouveau_devinit_destroy(&priv->base);
}

int
nv04_devinit_init(struct nouveau_object *object)
{
	struct nv04_devinit_priv *priv = (void *)object;

	if (!priv->base.post) {
		u32 htotal = nv_rdvgac(priv, 0, 0x06);
		htotal |= (nv_rdvgac(priv, 0, 0x07) & 0x01) << 8;
		htotal |= (nv_rdvgac(priv, 0, 0x07) & 0x20) << 4;
		htotal |= (nv_rdvgac(priv, 0, 0x25) & 0x01) << 10;
		htotal |= (nv_rdvgac(priv, 0, 0x41) & 0x01) << 11;
		if (!htotal) {
			nv_info(priv, "adaptor not initialised\n");
			priv->base.post = true;
		}
	}

	return nouveau_devinit_init(&priv->base);
}

int
nv04_devinit_fini(struct nouveau_object *object, bool suspend)
{
	struct nv04_devinit_priv *priv = (void *)object;

	/* make i2c busses accessible */
	nv_mask(priv, 0x000200, 0x00000001, 0x00000001);

	/* unlock extended vga crtc regs, and unslave crtcs */
	nv_lockvgac(priv, false);
	if (priv->owner < 0)
		priv->owner = nv_rdvgaowner(priv);
	nv_wrvgaowner(priv, 0);

	return nouveau_devinit_fini(&priv->base, suspend);
}

struct nouveau_oclass
nv04_devinit_oclass = {
	.handle = NV_SUBDEV(DEVINIT, 0x04),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv04_devinit_ctor,
		.dtor = nv04_devinit_dtor,
		.init = nv04_devinit_init,
		.fini = nv04_devinit_fini,
	},
};

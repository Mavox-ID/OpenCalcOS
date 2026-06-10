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

#define NV04_PFB_BOOT_0						0x00100000
#	define NV04_PFB_BOOT_0_RAM_AMOUNT			0x00000003
#	define NV04_PFB_BOOT_0_RAM_AMOUNT_32MB			0x00000000
#	define NV04_PFB_BOOT_0_RAM_AMOUNT_4MB			0x00000001
#	define NV04_PFB_BOOT_0_RAM_AMOUNT_8MB			0x00000002
#	define NV04_PFB_BOOT_0_RAM_AMOUNT_16MB			0x00000003
#	define NV04_PFB_BOOT_0_RAM_WIDTH_128			0x00000004
#	define NV04_PFB_BOOT_0_RAM_TYPE				0x00000028
#	define NV04_PFB_BOOT_0_RAM_TYPE_SGRAM_8MBIT		0x00000000
#	define NV04_PFB_BOOT_0_RAM_TYPE_SGRAM_16MBIT		0x00000008
#	define NV04_PFB_BOOT_0_RAM_TYPE_SGRAM_16MBIT_4BANK	0x00000010
#	define NV04_PFB_BOOT_0_RAM_TYPE_SDRAM_16MBIT		0x00000018
#	define NV04_PFB_BOOT_0_RAM_TYPE_SDRAM_64MBIT		0x00000020
#	define NV04_PFB_BOOT_0_RAM_TYPE_SDRAM_64MBITX16		0x00000028
#	define NV04_PFB_BOOT_0_UMA_ENABLE			0x00000100
#	define NV04_PFB_BOOT_0_UMA_SIZE				0x0000f000
#define NV04_PFB_CFG0						0x00100200

struct nv04_fb_priv {
	struct nouveau_fb base;
};

bool
nv04_fb_memtype_valid(struct nouveau_fb *pfb, u32 tile_flags)
{
	if (!(tile_flags & 0xff00))
		return true;

	return false;
}

static int
nv04_fb_vram_init(struct nouveau_fb *pfb)
{
	u32 boot0 = nv_rd32(pfb, NV04_PFB_BOOT_0);
	if (boot0 & 0x00000100) {
		pfb->ram.size  = ((boot0 >> 12) & 0xf) * 2 + 2;
		pfb->ram.size *= 1024 * 1024;
	} else {
		switch (boot0 & NV04_PFB_BOOT_0_RAM_AMOUNT) {
		case NV04_PFB_BOOT_0_RAM_AMOUNT_32MB:
			pfb->ram.size = 32 * 1024 * 1024;
			break;
		case NV04_PFB_BOOT_0_RAM_AMOUNT_16MB:
			pfb->ram.size = 16 * 1024 * 1024;
			break;
		case NV04_PFB_BOOT_0_RAM_AMOUNT_8MB:
			pfb->ram.size = 8 * 1024 * 1024;
			break;
		case NV04_PFB_BOOT_0_RAM_AMOUNT_4MB:
			pfb->ram.size = 4 * 1024 * 1024;
			break;
		}
	}

	if ((boot0 & 0x00000038) <= 0x10)
		pfb->ram.type = NV_MEM_TYPE_SGRAM;
	else
		pfb->ram.type = NV_MEM_TYPE_SDRAM;
	return 0;
}

static int
nv04_fb_init(struct nouveau_object *object)
{
	struct nv04_fb_priv *priv = (void *)object;
	int ret;

	ret = nouveau_fb_init(&priv->base);
	if (ret)
		return ret;

	/* This is what the DDX did for NV_ARCH_04, but a mmio-trace shows
	 * nvidia reading PFB_CFG_0, then writing back its original value.
	 * (which was 0x701114 in this case)
	 */
	nv_wr32(priv, NV04_PFB_CFG0, 0x1114);
	return 0;
}

static int
nv04_fb_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	     struct nouveau_oclass *oclass, void *data, u32 size,
	     struct nouveau_object **pobject)
{
	struct nv04_fb_priv *priv;
	int ret;

	ret = nouveau_fb_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.memtype_valid = nv04_fb_memtype_valid;
	priv->base.ram.init = nv04_fb_vram_init;
	return nouveau_fb_preinit(&priv->base);
}

struct nouveau_oclass
nv04_fb_oclass = {
	.handle = NV_SUBDEV(FB, 0x04),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv04_fb_ctor,
		.dtor = _nouveau_fb_dtor,
		.init = nv04_fb_init,
		.fini = _nouveau_fb_fini,
	},
};

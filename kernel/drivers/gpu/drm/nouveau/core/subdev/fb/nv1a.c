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

struct nv1a_fb_priv {
	struct nouveau_fb base;
};

static int
nv1a_fb_vram_init(struct nouveau_fb *pfb)
{
	struct pci_dev *bridge;
	u32 mem, mib;

	bridge = pci_get_bus_and_slot(0, PCI_DEVFN(0, 1));
	if (!bridge) {
		nv_fatal(pfb, "no bridge device\n");
		return -ENODEV;
	}

	if (nv_device(pfb)->chipset == 0x1a) {
		pci_read_config_dword(bridge, 0x7c, &mem);
		mib = ((mem >> 6) & 31) + 1;
	} else {
		pci_read_config_dword(bridge, 0x84, &mem);
		mib = ((mem >> 4) & 127) + 1;
	}

	pfb->ram.type = NV_MEM_TYPE_STOLEN;
	pfb->ram.size = mib * 1024 * 1024;
	return 0;
}

static int
nv1a_fb_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	     struct nouveau_oclass *oclass, void *data, u32 size,
	     struct nouveau_object **pobject)
{
	struct nv1a_fb_priv *priv;
	int ret;

	ret = nouveau_fb_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.memtype_valid = nv04_fb_memtype_valid;
	priv->base.ram.init = nv1a_fb_vram_init;
	priv->base.tile.regions = 8;
	priv->base.tile.init = nv10_fb_tile_init;
	priv->base.tile.fini = nv10_fb_tile_fini;
	priv->base.tile.prog = nv10_fb_tile_prog;
	return nouveau_fb_preinit(&priv->base);
}

struct nouveau_oclass
nv1a_fb_oclass = {
	.handle = NV_SUBDEV(FB, 0x1a),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv1a_fb_ctor,
		.dtor = _nouveau_fb_dtor,
		.init = _nouveau_fb_init,
		.fini = _nouveau_fb_fini,
	},
};

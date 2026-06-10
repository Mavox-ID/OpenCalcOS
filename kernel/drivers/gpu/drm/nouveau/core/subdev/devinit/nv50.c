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
#include <subdev/bios.h>
#include <subdev/bios/dcb.h>
#include <subdev/bios/disp.h>
#include <subdev/bios/init.h>
#include <subdev/devinit.h>
#include <subdev/vga.h>

struct nv50_devinit_priv {
	struct nouveau_devinit base;
};

static int
nv50_devinit_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		  struct nouveau_oclass *oclass, void *data, u32 size,
		  struct nouveau_object **pobject)
{
	struct nv50_devinit_priv *priv;
	int ret;

	ret = nouveau_devinit_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	return 0;
}

static void
nv50_devinit_dtor(struct nouveau_object *object)
{
	struct nv50_devinit_priv *priv = (void *)object;
	nouveau_devinit_destroy(&priv->base);
}

static int
nv50_devinit_init(struct nouveau_object *object)
{
	struct nouveau_bios *bios = nouveau_bios(object);
	struct nv50_devinit_priv *priv = (void *)object;
	struct nvbios_outp info;
	struct dcb_output outp;
	u8  ver = 0xff, hdr, cnt, len;
	int ret, i = 0;

	if (!priv->base.post) {
		if (!nv_rdvgac(priv, 0, 0x00) &&
		    !nv_rdvgac(priv, 0, 0x1a)) {
			nv_info(priv, "adaptor not initialised\n");
			priv->base.post = true;
		}
	}

	ret = nouveau_devinit_init(&priv->base);
	if (ret)
		return ret;

	/* if we ran the init tables, execute first script pointer for each
	 * display table output entry that has a matching dcb entry.
	 */
	while (priv->base.post && ver) {
		u16 data = nvbios_outp_parse(bios, i++, &ver, &hdr, &cnt, &len, &info);
		if (data && dcb_outp_match(bios, info.type, info.mask, &ver, &len, &outp)) {
			struct nvbios_init init = {
				.subdev = nv_subdev(priv),
				.bios = bios,
				.offset = info.script[0],
				.outp = &outp,
				.crtc = -1,
				.execute = 1,
			};

			nvbios_exec(&init);
		}
	};

	return 0;
}

static int
nv50_devinit_fini(struct nouveau_object *object, bool suspend)
{
	struct nv50_devinit_priv *priv = (void *)object;
	return nouveau_devinit_fini(&priv->base, suspend);
}

struct nouveau_oclass
nv50_devinit_oclass = {
	.handle = NV_SUBDEV(DEVINIT, 0x50),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv50_devinit_ctor,
		.dtor = nv50_devinit_dtor,
		.init = nv50_devinit_init,
		.fini = nv50_devinit_fini,
	},
};

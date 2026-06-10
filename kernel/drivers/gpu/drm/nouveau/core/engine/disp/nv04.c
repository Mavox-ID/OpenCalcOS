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
#include <engine/disp.h>

struct nv04_disp_priv {
	struct nouveau_disp base;
};

static struct nouveau_oclass
nv04_disp_sclass[] = {
	{},
};

static void
nv04_disp_intr_vblank(struct nv04_disp_priv *priv, int crtc)
{
	struct nouveau_disp *disp = &priv->base;
	if (disp->vblank.notify)
		disp->vblank.notify(disp->vblank.data, crtc);
}

static void
nv04_disp_intr(struct nouveau_subdev *subdev)
{
	struct nv04_disp_priv *priv = (void *)subdev;
	u32 crtc0 = nv_rd32(priv, 0x600100);
	u32 crtc1 = nv_rd32(priv, 0x602100);

	if (crtc0 & 0x00000001) {
		nv04_disp_intr_vblank(priv, 0);
		nv_wr32(priv, 0x600100, 0x00000001);
	}

	if (crtc1 & 0x00000001) {
		nv04_disp_intr_vblank(priv, 1);
		nv_wr32(priv, 0x602100, 0x00000001);
	}
}

static int
nv04_disp_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		  struct nouveau_oclass *oclass, void *data, u32 size,
		  struct nouveau_object **pobject)
{
	struct nv04_disp_priv *priv;
	int ret;

	ret = nouveau_disp_create(parent, engine, oclass, "DISPLAY",
				  "display", &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_engine(priv)->sclass = nv04_disp_sclass;
	nv_subdev(priv)->intr = nv04_disp_intr;
	return 0;
}

struct nouveau_oclass
nv04_disp_oclass = {
	.handle = NV_ENGINE(DISP, 0x04),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv04_disp_ctor,
		.dtor = _nouveau_disp_dtor,
		.init = _nouveau_disp_init,
		.fini = _nouveau_disp_fini,
	},
};

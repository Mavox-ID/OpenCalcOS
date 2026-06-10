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
#include <engine/software.h>
#include <engine/disp.h>

#include <core/class.h>

#include "nv50.h"

static struct nouveau_oclass
nve0_disp_sclass[] = {
	{ NVE0_DISP_MAST_CLASS, &nvd0_disp_mast_ofuncs },
	{ NVE0_DISP_SYNC_CLASS, &nvd0_disp_sync_ofuncs },
	{ NVE0_DISP_OVLY_CLASS, &nvd0_disp_ovly_ofuncs },
	{ NVE0_DISP_OIMM_CLASS, &nvd0_disp_oimm_ofuncs },
	{ NVE0_DISP_CURS_CLASS, &nvd0_disp_curs_ofuncs },
	{}
};

static struct nouveau_oclass
nve0_disp_base_oclass[] = {
	{ NVE0_DISP_CLASS, &nvd0_disp_base_ofuncs, nva3_disp_base_omthds },
	{}
};

static int
nve0_disp_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	       struct nouveau_oclass *oclass, void *data, u32 size,
	       struct nouveau_object **pobject)
{
	struct nv50_disp_priv *priv;
	int ret;

	ret = nouveau_disp_create(parent, engine, oclass, "PDISP",
				  "display", &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_engine(priv)->sclass = nve0_disp_base_oclass;
	nv_engine(priv)->cclass = &nv50_disp_cclass;
	nv_subdev(priv)->intr = nvd0_disp_intr;
	priv->sclass = nve0_disp_sclass;
	priv->head.nr = nv_rd32(priv, 0x022448);
	priv->dac.nr = 3;
	priv->sor.nr = 4;
	priv->dac.power = nv50_dac_power;
	priv->dac.sense = nv50_dac_sense;
	priv->sor.power = nv50_sor_power;
	priv->sor.hda_eld = nvd0_hda_eld;
	priv->sor.hdmi = nvd0_hdmi_ctrl;
	priv->sor.dp_train = nvd0_sor_dp_train;
	priv->sor.dp_train_init = nv94_sor_dp_train_init;
	priv->sor.dp_train_fini = nv94_sor_dp_train_fini;
	priv->sor.dp_lnkctl = nvd0_sor_dp_lnkctl;
	priv->sor.dp_drvctl = nvd0_sor_dp_drvctl;

	INIT_LIST_HEAD(&priv->base.vblank.list);
	spin_lock_init(&priv->base.vblank.lock);
	return 0;
}

struct nouveau_oclass
nve0_disp_oclass = {
	.handle = NV_ENGINE(DISP, 0x91),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nve0_disp_ctor,
		.dtor = _nouveau_disp_dtor,
		.init = _nouveau_disp_init,
		.fini = _nouveau_disp_fini,
	},
};

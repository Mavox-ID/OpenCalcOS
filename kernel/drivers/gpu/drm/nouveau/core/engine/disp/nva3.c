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
nva3_disp_sclass[] = {
	{ NVA3_DISP_MAST_CLASS, &nv50_disp_mast_ofuncs },
	{ NVA3_DISP_SYNC_CLASS, &nv50_disp_sync_ofuncs },
	{ NVA3_DISP_OVLY_CLASS, &nv50_disp_ovly_ofuncs },
	{ NVA3_DISP_OIMM_CLASS, &nv50_disp_oimm_ofuncs },
	{ NVA3_DISP_CURS_CLASS, &nv50_disp_curs_ofuncs },
	{}
};

struct nouveau_omthds
nva3_disp_base_omthds[] = {
	{ SOR_MTHD(NV50_DISP_SOR_PWR)         , nv50_sor_mthd },
	{ SOR_MTHD(NVA3_DISP_SOR_HDA_ELD)     , nv50_sor_mthd },
	{ SOR_MTHD(NV84_DISP_SOR_HDMI_PWR)    , nv50_sor_mthd },
	{ SOR_MTHD(NV50_DISP_SOR_LVDS_SCRIPT) , nv50_sor_mthd },
	{ SOR_MTHD(NV94_DISP_SOR_DP_TRAIN)    , nv50_sor_mthd },
	{ SOR_MTHD(NV94_DISP_SOR_DP_LNKCTL)   , nv50_sor_mthd },
	{ SOR_MTHD(NV94_DISP_SOR_DP_DRVCTL(0)), nv50_sor_mthd },
	{ SOR_MTHD(NV94_DISP_SOR_DP_DRVCTL(1)), nv50_sor_mthd },
	{ SOR_MTHD(NV94_DISP_SOR_DP_DRVCTL(2)), nv50_sor_mthd },
	{ SOR_MTHD(NV94_DISP_SOR_DP_DRVCTL(3)), nv50_sor_mthd },
	{ DAC_MTHD(NV50_DISP_DAC_PWR)         , nv50_dac_mthd },
	{ DAC_MTHD(NV50_DISP_DAC_LOAD)        , nv50_dac_mthd },
	{},
};

static struct nouveau_oclass
nva3_disp_base_oclass[] = {
	{ NVA3_DISP_CLASS, &nv50_disp_base_ofuncs, nva3_disp_base_omthds },
	{}
};

static int
nva3_disp_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
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

	nv_engine(priv)->sclass = nva3_disp_base_oclass;
	nv_engine(priv)->cclass = &nv50_disp_cclass;
	nv_subdev(priv)->intr = nv50_disp_intr;
	priv->sclass = nva3_disp_sclass;
	priv->head.nr = 2;
	priv->dac.nr = 3;
	priv->sor.nr = 4;
	priv->dac.power = nv50_dac_power;
	priv->dac.sense = nv50_dac_sense;
	priv->sor.power = nv50_sor_power;
	priv->sor.hda_eld = nva3_hda_eld;
	priv->sor.hdmi = nva3_hdmi_ctrl;
	priv->sor.dp_train = nv94_sor_dp_train;
	priv->sor.dp_train_init = nv94_sor_dp_train_init;
	priv->sor.dp_train_fini = nv94_sor_dp_train_fini;
	priv->sor.dp_lnkctl = nv94_sor_dp_lnkctl;
	priv->sor.dp_drvctl = nv94_sor_dp_drvctl;

	INIT_LIST_HEAD(&priv->base.vblank.list);
	spin_lock_init(&priv->base.vblank.lock);
	return 0;
}

struct nouveau_oclass
nva3_disp_oclass = {
	.handle = NV_ENGINE(DISP, 0x85),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nva3_disp_ctor,
		.dtor = _nouveau_disp_dtor,
		.init = _nouveau_disp_init,
		.fini = _nouveau_disp_fini,
	},
};

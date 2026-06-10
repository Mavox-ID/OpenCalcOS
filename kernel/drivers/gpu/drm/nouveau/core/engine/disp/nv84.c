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
nv84_disp_sclass[] = {
	{ NV84_DISP_MAST_CLASS, &nv50_disp_mast_ofuncs },
	{ NV84_DISP_SYNC_CLASS, &nv50_disp_sync_ofuncs },
	{ NV84_DISP_OVLY_CLASS, &nv50_disp_ovly_ofuncs },
	{ NV84_DISP_OIMM_CLASS, &nv50_disp_oimm_ofuncs },
	{ NV84_DISP_CURS_CLASS, &nv50_disp_curs_ofuncs },
	{}
};

struct nouveau_omthds
nv84_disp_base_omthds[] = {
	{ SOR_MTHD(NV50_DISP_SOR_PWR)         , nv50_sor_mthd },
	{ SOR_MTHD(NV84_DISP_SOR_HDMI_PWR)    , nv50_sor_mthd },
	{ SOR_MTHD(NV50_DISP_SOR_LVDS_SCRIPT) , nv50_sor_mthd },
	{ DAC_MTHD(NV50_DISP_DAC_PWR)         , nv50_dac_mthd },
	{ DAC_MTHD(NV50_DISP_DAC_LOAD)        , nv50_dac_mthd },
	{},
};

static struct nouveau_oclass
nv84_disp_base_oclass[] = {
	{ NV84_DISP_CLASS, &nv50_disp_base_ofuncs, nv84_disp_base_omthds },
	{}
};

static int
nv84_disp_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
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

	nv_engine(priv)->sclass = nv84_disp_base_oclass;
	nv_engine(priv)->cclass = &nv50_disp_cclass;
	nv_subdev(priv)->intr = nv50_disp_intr;
	priv->sclass = nv84_disp_sclass;
	priv->head.nr = 2;
	priv->dac.nr = 3;
	priv->sor.nr = 2;
	priv->dac.power = nv50_dac_power;
	priv->dac.sense = nv50_dac_sense;
	priv->sor.power = nv50_sor_power;
	priv->sor.hdmi = nv84_hdmi_ctrl;

	INIT_LIST_HEAD(&priv->base.vblank.list);
	spin_lock_init(&priv->base.vblank.lock);
	return 0;
}

struct nouveau_oclass
nv84_disp_oclass = {
	.handle = NV_ENGINE(DISP, 0x82),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv84_disp_ctor,
		.dtor = _nouveau_disp_dtor,
		.init = _nouveau_disp_init,
		.fini = _nouveau_disp_fini,
	},
};

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
#include <subdev/clock.h>
#include <subdev/bios.h>
#include <subdev/bios/pll.h>

#include "pll.h"

struct nva3_clock_priv {
	struct nouveau_clock base;
};

static int
nva3_clock_pll_set(struct nouveau_clock *clk, u32 type, u32 freq)
{
	struct nva3_clock_priv *priv = (void *)clk;
	struct nouveau_bios *bios = nouveau_bios(priv);
	struct nvbios_pll info;
	int N, fN, M, P;
	int ret;

	ret = nvbios_pll_parse(bios, type, &info);
	if (ret)
		return ret;

	ret = nva3_pll_calc(clk, &info, freq, &N, &fN, &M, &P);
	if (ret < 0)
		return ret;

	switch (info.type) {
	case PLL_VPLL0:
	case PLL_VPLL1:
		nv_wr32(priv, info.reg + 0, 0x50000610);
		nv_mask(priv, info.reg + 4, 0x003fffff,
					    (P << 16) | (M << 8) | N);
		nv_wr32(priv, info.reg + 8, fN);
		break;
	default:
		nv_warn(priv, "0x%08x/%dKhz unimplemented\n", type, freq);
		ret = -EINVAL;
		break;
	}

	return ret;
}

int
nva3_clock_pll_calc(struct nouveau_clock *clock, struct nvbios_pll *info,
		    int clk, struct nouveau_pll_vals *pv)
{
	int ret, N, M, P;

	ret = nva3_pll_calc(clock, info, clk, &N, NULL, &M, &P);

	if (ret > 0) {
		pv->refclk = info->refclk;
		pv->N1 = N;
		pv->M1 = M;
		pv->log2P = P;
	}
	return ret;
}


static int
nva3_clock_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		struct nouveau_oclass *oclass, void *data, u32 size,
		struct nouveau_object **pobject)
{
	struct nva3_clock_priv *priv;
	int ret;

	ret = nouveau_clock_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.pll_set = nva3_clock_pll_set;
	priv->base.pll_calc = nva3_clock_pll_calc;
	return 0;
}

struct nouveau_oclass
nva3_clock_oclass = {
	.handle = NV_SUBDEV(CLOCK, 0xa3),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nva3_clock_ctor,
		.dtor = _nouveau_clock_dtor,
		.init = _nouveau_clock_init,
		.fini = _nouveau_clock_fini,
	},
};

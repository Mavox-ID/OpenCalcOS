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

struct nvc0_clock_priv {
	struct nouveau_clock base;
};

static int
nvc0_clock_pll_set(struct nouveau_clock *clk, u32 type, u32 freq)
{
	struct nvc0_clock_priv *priv = (void *)clk;
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
	case PLL_VPLL2:
	case PLL_VPLL3:
		nv_mask(priv, info.reg + 0x0c, 0x00000000, 0x00000100);
		nv_wr32(priv, info.reg + 0x04, (P << 16) | (N << 8) | M);
		nv_wr32(priv, info.reg + 0x10, fN << 16);
		break;
	default:
		nv_warn(priv, "0x%08x/%dKhz unimplemented\n", type, freq);
		ret = -EINVAL;
		break;
	}

	return ret;
}

static int
nvc0_clock_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		struct nouveau_oclass *oclass, void *data, u32 size,
		struct nouveau_object **pobject)
{
	struct nvc0_clock_priv *priv;
	int ret;

	ret = nouveau_clock_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.pll_set = nvc0_clock_pll_set;
	priv->base.pll_calc = nva3_clock_pll_calc;
	return 0;
}

struct nouveau_oclass
nvc0_clock_oclass = {
	.handle = NV_SUBDEV(CLOCK, 0xc0),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nvc0_clock_ctor,
		.dtor = _nouveau_clock_dtor,
		.init = _nouveau_clock_init,
		.fini = _nouveau_clock_fini,
	},
};

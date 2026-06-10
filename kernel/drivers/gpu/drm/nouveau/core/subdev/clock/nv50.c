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

struct nv50_clock_priv {
	struct nouveau_clock base;
};

static int
nv50_clock_pll_set(struct nouveau_clock *clk, u32 type, u32 freq)
{
	struct nv50_clock_priv *priv = (void *)clk;
	struct nouveau_bios *bios = nouveau_bios(priv);
	struct nvbios_pll info;
	int N1, M1, N2, M2, P;
	int ret;

	ret = nvbios_pll_parse(bios, type, &info);
	if (ret) {
		nv_error(clk, "failed to retrieve pll data, %d\n", ret);
		return ret;
	}

	ret = nv04_pll_calc(clk, &info, freq, &N1, &M1, &N2, &M2, &P);
	if (!ret) {
		nv_error(clk, "failed pll calculation\n");
		return ret;
	}

	switch (info.type) {
	case PLL_VPLL0:
	case PLL_VPLL1:
		nv_wr32(priv, info.reg + 0, 0x10000611);
		nv_mask(priv, info.reg + 4, 0x00ff00ff, (M1 << 16) | N1);
		nv_mask(priv, info.reg + 8, 0x7fff00ff, (P  << 28) |
							(M2 << 16) | N2);
		break;
	case PLL_MEMORY:
		nv_mask(priv, info.reg + 0, 0x01ff0000, (P << 22) |
						        (info.bias_p << 19) |
							(P << 16));
		nv_wr32(priv, info.reg + 4, (N1 << 8) | M1);
		break;
	default:
		nv_mask(priv, info.reg + 0, 0x00070000, (P << 16));
		nv_wr32(priv, info.reg + 4, (N1 << 8) | M1);
		break;
	}

	return 0;
}

static int
nv50_clock_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		struct nouveau_oclass *oclass, void *data, u32 size,
		struct nouveau_object **pobject)
{
	struct nv50_clock_priv *priv;
	int ret;

	ret = nouveau_clock_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.pll_set = nv50_clock_pll_set;
	priv->base.pll_calc = nv04_clock_pll_calc;
	return 0;
}

struct nouveau_oclass
nv50_clock_oclass = {
	.handle = NV_SUBDEV(CLOCK, 0x50),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv50_clock_ctor,
		.dtor = _nouveau_clock_dtor,
		.init = _nouveau_clock_init,
		.fini = _nouveau_clock_fini,
	},
};

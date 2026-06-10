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
#include <subdev/ltcg.h>

struct nvc0_ltcg_priv {
	struct nouveau_ltcg base;
	u32 subp_nr;
};

static void
nvc0_ltcg_subp_isr(struct nvc0_ltcg_priv *priv, int unit, int subp)
{
	u32 subp_base = 0x141000 + (unit * 0x2000) + (subp * 0x400);
	u32 stat = nv_rd32(priv, subp_base + 0x020);

	if (stat) {
		nv_info(priv, "LTC%d_LTS%d: 0x%08x\n", unit, subp, stat);
		nv_wr32(priv, subp_base + 0x020, stat);
	}
}

static void
nvc0_ltcg_intr(struct nouveau_subdev *subdev)
{
	struct nvc0_ltcg_priv *priv = (void *)subdev;
	u32 units;

	units = nv_rd32(priv, 0x00017c);
	while (units) {
		u32 subp, unit = ffs(units) - 1;
		for (subp = 0; subp < priv->subp_nr; subp++)
			nvc0_ltcg_subp_isr(priv, unit, subp);
		units &= ~(1 << unit);
	}

	/* we do something horribly wrong and upset PMFB a lot, so mask off
	 * interrupts from it after the first one until it's fixed
	 */
	nv_mask(priv, 0x000640, 0x02000000, 0x00000000);
}

static int
nvc0_ltcg_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	       struct nouveau_oclass *oclass, void *data, u32 size,
	       struct nouveau_object **pobject)
{
	struct nvc0_ltcg_priv *priv;
	int ret;

	ret = nouveau_ltcg_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->subp_nr = nv_rd32(priv, 0x17e8dc) >> 24;
	nv_mask(priv, 0x17e820, 0x00100000, 0x00000000); /* INTR_EN &= ~0x10 */

	nv_subdev(priv)->intr = nvc0_ltcg_intr;
	return 0;
}

struct nouveau_oclass
nvc0_ltcg_oclass = {
	.handle = NV_SUBDEV(LTCG, 0xc0),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nvc0_ltcg_ctor,
		.dtor = _nouveau_ltcg_dtor,
		.init = _nouveau_ltcg_init,
		.fini = _nouveau_ltcg_fini,
	},
};

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
#include <core/os.h>
#include <core/class.h>
#include <core/engctx.h>

#include <subdev/vm.h>
#include <subdev/bar.h>
#include <subdev/timer.h>

#include <engine/mpeg.h>

struct nv84_mpeg_priv {
	struct nouveau_mpeg base;
};

struct nv84_mpeg_chan {
	struct nouveau_mpeg_chan base;
};

/*******************************************************************************
 * MPEG object classes
 ******************************************************************************/

static struct nouveau_oclass
nv84_mpeg_sclass[] = {
	{ 0x8274, &nv50_mpeg_ofuncs },
	{}
};

/*******************************************************************************
 * PMPEG context
 ******************************************************************************/

static struct nouveau_oclass
nv84_mpeg_cclass = {
	.handle = NV_ENGCTX(MPEG, 0x84),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv50_mpeg_context_ctor,
		.dtor = _nouveau_mpeg_context_dtor,
		.init = _nouveau_mpeg_context_init,
		.fini = _nouveau_mpeg_context_fini,
		.rd32 = _nouveau_mpeg_context_rd32,
		.wr32 = _nouveau_mpeg_context_wr32,
	},
};

/*******************************************************************************
 * PMPEG engine/subdev functions
 ******************************************************************************/

static int
nv84_mpeg_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	       struct nouveau_oclass *oclass, void *data, u32 size,
	       struct nouveau_object **pobject)
{
	struct nv84_mpeg_priv *priv;
	int ret;

	ret = nouveau_mpeg_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->unit = 0x00000002;
	nv_subdev(priv)->intr = nv50_mpeg_intr;
	nv_engine(priv)->cclass = &nv84_mpeg_cclass;
	nv_engine(priv)->sclass = nv84_mpeg_sclass;
	nv_engine(priv)->tlb_flush = nv50_mpeg_tlb_flush;
	return 0;
}

struct nouveau_oclass
nv84_mpeg_oclass = {
	.handle = NV_ENGINE(MPEG, 0x84),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv84_mpeg_ctor,
		.dtor = _nouveau_mpeg_dtor,
		.init = nv50_mpeg_init,
		.fini = _nouveau_mpeg_fini,
	},
};

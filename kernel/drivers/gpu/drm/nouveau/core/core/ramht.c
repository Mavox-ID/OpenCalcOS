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
#include <core/object.h>
#include <core/ramht.h>
#include <core/math.h>

#include <subdev/bar.h>

static u32
nouveau_ramht_hash(struct nouveau_ramht *ramht, int chid, u32 handle)
{
	u32 hash = 0;

	while (handle) {
		hash ^= (handle & ((1 << ramht->bits) - 1));
		handle >>= ramht->bits;
	}

	hash ^= chid << (ramht->bits - 4);
	hash  = hash << 3;
	return hash;
}

int
nouveau_ramht_insert(struct nouveau_ramht *ramht, int chid,
		     u32 handle, u32 context)
{
	struct nouveau_bar *bar = nouveau_bar(ramht);
	u32 co, ho;

	co = ho = nouveau_ramht_hash(ramht, chid, handle);
	do {
		if (!nv_ro32(ramht, co + 4)) {
			nv_wo32(ramht, co + 0, handle);
			nv_wo32(ramht, co + 4, context);
			if (bar)
				bar->flush(bar);
			return co;
		}

		co += 8;
		if (co >= nv_gpuobj(ramht)->size)
			co = 0;
	} while (co != ho);

	return -ENOMEM;
}

void
nouveau_ramht_remove(struct nouveau_ramht *ramht, int cookie)
{
	struct nouveau_bar *bar = nouveau_bar(ramht);
	nv_wo32(ramht, cookie + 0, 0x00000000);
	nv_wo32(ramht, cookie + 4, 0x00000000);
	if (bar)
		bar->flush(bar);
}

static struct nouveau_oclass
nouveau_ramht_oclass = {
	.handle = 0x0000abcd,
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = NULL,
		.dtor = _nouveau_gpuobj_dtor,
		.init = _nouveau_gpuobj_init,
		.fini = _nouveau_gpuobj_fini,
		.rd32 = _nouveau_gpuobj_rd32,
		.wr32 = _nouveau_gpuobj_wr32,
	},
};

int
nouveau_ramht_new(struct nouveau_object *parent, struct nouveau_object *pargpu,
		  u32 size, u32 align, struct nouveau_ramht **pramht)
{
	struct nouveau_ramht *ramht;
	int ret;

	ret = nouveau_gpuobj_create(parent, parent->engine ?
				    parent->engine : parent, /* <nv50 ramht */
				    &nouveau_ramht_oclass, 0, pargpu, size,
				    align, NVOBJ_FLAG_ZERO_ALLOC, &ramht);
	*pramht = ramht;
	if (ret)
		return ret;

	ramht->bits = log2i(nv_gpuobj(ramht)->size >> 3);
	return 0;
}

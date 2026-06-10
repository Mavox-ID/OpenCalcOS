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
#include "subdev/fb.h"
#include "subdev/bios.h"
#include "subdev/bios/bit.h"

int
nouveau_fb_bios_memtype(struct nouveau_bios *bios)
{
	struct bit_entry M;
	u8 ramcfg;

	ramcfg = (nv_rd32(bios, 0x101000) & 0x0000003c) >> 2;
	if (!bit_entry(bios, 'M', &M) && M.version == 2 && M.length >= 5) {
		u16 table   = nv_ro16(bios, M.offset + 3);
		u8  version = nv_ro08(bios, table + 0);
		u8  header  = nv_ro08(bios, table + 1);
		u8  record  = nv_ro08(bios, table + 2);
		u8  entries = nv_ro08(bios, table + 3);
		if (table && version == 0x10 && ramcfg < entries) {
			u16 entry = table + header + (ramcfg * record);
			switch (nv_ro08(bios, entry) & 0x0f) {
			case 0: return NV_MEM_TYPE_DDR2;
			case 1: return NV_MEM_TYPE_DDR3;
			case 2: return NV_MEM_TYPE_GDDR3;
			case 3: return NV_MEM_TYPE_GDDR5;
			default:
				break;
			}

		}
	}

	return NV_MEM_TYPE_UNKNOWN;
}

int
nouveau_fb_preinit(struct nouveau_fb *pfb)
{
	static const char *name[] = {
		[NV_MEM_TYPE_UNKNOWN] = "unknown",
		[NV_MEM_TYPE_STOLEN ] = "stolen system memory",
		[NV_MEM_TYPE_SGRAM  ] = "SGRAM",
		[NV_MEM_TYPE_SDRAM  ] = "SDRAM",
		[NV_MEM_TYPE_DDR1   ] = "DDR1",
		[NV_MEM_TYPE_DDR2   ] = "DDR2",
		[NV_MEM_TYPE_DDR3   ] = "DDR3",
		[NV_MEM_TYPE_GDDR2  ] = "GDDR2",
		[NV_MEM_TYPE_GDDR3  ] = "GDDR3",
		[NV_MEM_TYPE_GDDR4  ] = "GDDR4",
		[NV_MEM_TYPE_GDDR5  ] = "GDDR5",
	};
	int ret, tags;

	tags = pfb->ram.init(pfb);
	if (tags < 0 || !pfb->ram.size) {
		nv_fatal(pfb, "error detecting memory configuration!!\n");
		return (tags < 0) ? tags : -ERANGE;
	}

	if (!nouveau_mm_initialised(&pfb->vram)) {
		ret = nouveau_mm_init(&pfb->vram, 0, pfb->ram.size >> 12, 1);
		if (ret)
			return ret;
	}

	if (!nouveau_mm_initialised(&pfb->tags) && tags) {
		ret = nouveau_mm_init(&pfb->tags, 0, ++tags, 1);
		if (ret)
			return ret;
	}

	nv_info(pfb, "RAM type: %s\n", name[pfb->ram.type]);
	nv_info(pfb, "RAM size: %d MiB\n", (int)(pfb->ram.size >> 20));
	nv_info(pfb, "   ZCOMP: %d tags\n", tags);
	return 0;
}

void
nouveau_fb_destroy(struct nouveau_fb *pfb)
{
	int i;

	for (i = 0; i < pfb->tile.regions; i++)
		pfb->tile.fini(pfb, i, &pfb->tile.region[i]);
	nouveau_mm_fini(&pfb->tags);
	nouveau_mm_fini(&pfb->vram);

	nouveau_subdev_destroy(&pfb->base);
}

void
_nouveau_fb_dtor(struct nouveau_object *object)
{
	struct nouveau_fb *pfb = (void *)object;
	nouveau_fb_destroy(pfb);
}
int
nouveau_fb_init(struct nouveau_fb *pfb)
{
	int ret, i;

	ret = nouveau_subdev_init(&pfb->base);
	if (ret)
		return ret;

	for (i = 0; i < pfb->tile.regions; i++)
		pfb->tile.prog(pfb, i, &pfb->tile.region[i]);

	return 0;
}

int
_nouveau_fb_init(struct nouveau_object *object)
{
	struct nouveau_fb *pfb = (void *)object;
	return nouveau_fb_init(pfb);
}

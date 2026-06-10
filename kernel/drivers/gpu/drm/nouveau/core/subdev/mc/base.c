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
#include <subdev/mc.h>

void
nouveau_mc_intr(struct nouveau_subdev *subdev)
{
	struct nouveau_mc *pmc = nouveau_mc(subdev);
	const struct nouveau_mc_intr *map = pmc->intr_map;
	struct nouveau_subdev *unit;
	u32 stat, intr;

	intr = stat = nv_rd32(pmc, 0x000100);
	while (stat && map->stat) {
		if (stat & map->stat) {
			unit = nouveau_subdev(subdev, map->unit);
			if (unit && unit->intr)
				unit->intr(unit);
			intr &= ~map->stat;
		}
		map++;
	}

	if (intr) {
		nv_error(pmc, "unknown intr 0x%08x\n", stat);
	}
}

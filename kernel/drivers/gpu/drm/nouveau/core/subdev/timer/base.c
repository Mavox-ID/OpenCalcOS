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
#include "subdev/timer.h"

bool
nouveau_timer_wait_eq(void *obj, u64 nsec, u32 addr, u32 mask, u32 data)
{
	struct nouveau_timer *ptimer = nouveau_timer(obj);
	u64 time0;

	time0 = ptimer->read(ptimer);
	do {
		if (nv_iclass(obj, NV_SUBDEV_CLASS)) {
			if ((nv_rd32(obj, addr) & mask) == data)
				return true;
		} else {
			if ((nv_ro32(obj, addr) & mask) == data)
				return true;
		}
	} while (ptimer->read(ptimer) - time0 < nsec);

	return false;
}

bool
nouveau_timer_wait_ne(void *obj, u64 nsec, u32 addr, u32 mask, u32 data)
{
	struct nouveau_timer *ptimer = nouveau_timer(obj);
	u64 time0;

	time0 = ptimer->read(ptimer);
	do {
		if (nv_iclass(obj, NV_SUBDEV_CLASS)) {
			if ((nv_rd32(obj, addr) & mask) != data)
				return true;
		} else {
			if ((nv_ro32(obj, addr) & mask) != data)
				return true;
		}
	} while (ptimer->read(ptimer) - time0 < nsec);

	return false;
}

bool
nouveau_timer_wait_cb(void *obj, u64 nsec, bool (*func)(void *), void *data)
{
	struct nouveau_timer *ptimer = nouveau_timer(obj);
	u64 time0;

	time0 = ptimer->read(ptimer);
	do {
		if (func(data) == true)
			return true;
	} while (ptimer->read(ptimer) - time0 < nsec);

	return false;
}

void
nouveau_timer_alarm(void *obj, u32 nsec, struct nouveau_alarm *alarm)
{
	struct nouveau_timer *ptimer = nouveau_timer(obj);
	ptimer->alarm(ptimer, nsec, alarm);
}

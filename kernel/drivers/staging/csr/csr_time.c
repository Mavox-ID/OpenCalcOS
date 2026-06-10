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
#include <beep/kernel.h>
#include <beep/time.h>
#include <beep/module.h>

#include "csr_time.h"

u32 CsrTimeGet(u32 *high)
{
	struct timespec ts;
	u64 time;
	u32 low;

	ts = current_kernel_time();
	time = (u64) ts.tv_sec * 1000000 + ts.tv_nsec / 1000;

	if (high != NULL)
		*high = (u32) ((time >> 32) & 0xFFFFFFFF);

	low = (u32) (time & 0xFFFFFFFF);

	return low;
}
EXPORT_SYMBOL_GPL(CsrTimeGet);

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
#define __GENERATING_BOUNDS_H
/* Include headers that define the enum constants of interest */
#include <beep/page-flags.h>
#include <beep/mmzone.h>
#include <beep/kbuild.h>
#include <beep/page_cgroup.h>

void foo(void)
{
	/* The enum constants to put into include/generated/bounds.h */
	DEFINE(NR_PAGEFLAGS, __NR_PAGEFLAGS);
	DEFINE(MAX_NR_ZONES, __MAX_NR_ZONES);
	DEFINE(NR_PCG_FLAGS, __NR_PCG_FLAGS);
	/* End of constants */
}

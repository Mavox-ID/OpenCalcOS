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
#ifndef __MACH_TEGRA_IRAMMAP_H
#define __MACH_TEGRA_IRAMMAP_H

#include <asm/sizes.h>

/* The first 1K of IRAM is permanently reserved for the CPU reset handler */
#define TEGRA_IRAM_RESET_HANDLER_OFFSET	0
#define TEGRA_IRAM_RESET_HANDLER_SIZE	SZ_1K

#endif

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
#ifndef _CPQPHP_NVRAM_H
#define _CPQPHP_NVRAM_H

#ifndef CONFIG_HOTPLUG_PCI_COMPAQ_NVRAM

static inline void compaq_nvram_init (void __iomem *rom_start)
{
	return;
}

static inline int compaq_nvram_load (void __iomem *rom_start, struct controller *ctrl)
{
	return 0;
}

static inline int compaq_nvram_store (void __iomem *rom_start)
{
	return 0;
}

#else

extern void compaq_nvram_init	(void __iomem *rom_start);
extern int compaq_nvram_load	(void __iomem *rom_start, struct controller *ctrl);
extern int compaq_nvram_store	(void __iomem *rom_start);

#endif

#endif


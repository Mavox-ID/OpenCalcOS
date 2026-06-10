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
#ifndef __ASM_ARCH_MEMORY_H
#define __ASM_ARCH_MEMORY_H

#if defined(CONFIG_EP93XX_SDCE3_SYNC_PHYS_OFFSET)
#define PLAT_PHYS_OFFSET		UL(0x00000000)
#elif defined(CONFIG_EP93XX_SDCE0_PHYS_OFFSET)
#define PLAT_PHYS_OFFSET		UL(0xc0000000)
#elif defined(CONFIG_EP93XX_SDCE1_PHYS_OFFSET)
#define PLAT_PHYS_OFFSET		UL(0xd0000000)
#elif defined(CONFIG_EP93XX_SDCE2_PHYS_OFFSET)
#define PLAT_PHYS_OFFSET		UL(0xe0000000)
#elif defined(CONFIG_EP93XX_SDCE3_ASYNC_PHYS_OFFSET)
#define PLAT_PHYS_OFFSET		UL(0xf0000000)
#else
#error "Kconfig bug: No EP93xx PHYS_OFFSET set"
#endif

#endif

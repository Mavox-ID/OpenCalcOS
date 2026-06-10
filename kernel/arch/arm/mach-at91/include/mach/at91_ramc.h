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
#ifndef __AT91_RAMC_H__
#define __AT91_RAMC_H__

#ifndef __ASSEMBLY__
extern void __iomem *at91_ramc_base[];

#define at91_ramc_read(id, field) \
	__raw_readl(at91_ramc_base[id] + field)

#define at91_ramc_write(id, field, value) \
	__raw_writel(value, at91_ramc_base[id] + field)
#else
.extern at91_ramc_base
#endif

#define AT91_MEMCTRL_MC		0
#define AT91_MEMCTRL_SDRAMC	1
#define AT91_MEMCTRL_DDRSDR	2

#include <mach/at91rm9200_sdramc.h>
#include <mach/at91sam9_ddrsdr.h>
#include <mach/at91sam9_sdramc.h>

#endif /* __AT91_RAMC_H__ */

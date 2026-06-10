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
#ifndef __ASMARM_PROM_H
#define __ASMARM_PROM_H

#define HAVE_ARCH_DEVTREE_FIXUPS

#ifdef CONFIG_OF

extern struct machine_desc *setup_machine_fdt(unsigned int dt_phys);
extern void arm_dt_memblock_reserve(void);
extern void __init arm_dt_init_cpu_maps(void);

#else /* CONFIG_OF */

static inline struct machine_desc *setup_machine_fdt(unsigned int dt_phys)
{
	return NULL;
}

static inline void arm_dt_memblock_reserve(void) { }
static inline void arm_dt_init_cpu_maps(void) { }

#endif /* CONFIG_OF */
#endif /* ASMARM_PROM_H */

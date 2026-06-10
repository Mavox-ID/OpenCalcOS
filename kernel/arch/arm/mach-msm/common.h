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
#ifndef __MACH_COMMON_H
#define __MACH_COMMON_H

extern struct sys_timer msm7x01_timer;
extern struct sys_timer msm7x30_timer;
extern struct sys_timer msm_dt_timer;
extern struct sys_timer qsd8x50_timer;

extern void msm_map_common_io(void);
extern void msm_map_msm7x30_io(void);
extern void msm_map_msm8x60_io(void);
extern void msm_map_msm8960_io(void);
extern void msm_map_qsd8x50_io(void);

extern void __iomem *__msm_ioremap_caller(unsigned long phys_addr, size_t size,
					  unsigned int mtype, void *caller);

extern struct smp_operations msm_smp_ops;
extern void msm_cpu_die(unsigned int cpu);

#endif

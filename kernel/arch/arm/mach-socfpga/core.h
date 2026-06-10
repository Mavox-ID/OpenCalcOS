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
#ifndef __MACH_CORE_H
#define __MACH_CORE_H

extern void secondary_startup(void);
extern void __iomem *socfpga_scu_base_addr;

extern void socfpga_init_clocks(void);
extern void socfpga_sysmgr_init(void);

extern struct smp_operations socfpga_smp_ops;
extern char secondary_trampoline, secondary_trampoline_end;

#define SOCFPGA_SCU_VIRT_BASE   0xfffec000

#endif

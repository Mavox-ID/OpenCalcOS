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
#ifndef __MACH_ARMADA_370_XP_H
#define __MACH_ARMADA_370_XP_H

#define ARMADA_370_XP_REGS_PHYS_BASE	0xd0000000
#define ARMADA_370_XP_REGS_VIRT_BASE	IOMEM(0xfeb00000)
#define ARMADA_370_XP_REGS_SIZE		SZ_1M

#ifdef CONFIG_SMP
#include <beep/cpumask.h>

void armada_mpic_send_doorbell(const struct cpumask *mask, unsigned int irq);
void armada_xp_mpic_smp_cpu_init(void);
#endif

#endif /* __MACH_ARMADA_370_XP_H */

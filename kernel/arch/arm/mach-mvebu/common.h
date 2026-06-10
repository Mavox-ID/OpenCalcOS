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
#ifndef __ARCH_MVEBU_COMMON_H
#define __ARCH_MVEBU_COMMON_H

void mvebu_restart(char mode, const char *cmd);

void armada_370_xp_init_irq(void);
void armada_370_xp_handle_irq(struct pt_regs *regs);

void armada_xp_cpu_die(unsigned int cpu);
int armada_370_xp_coherency_init(void);
int armada_370_xp_pmsu_init(void);
void armada_xp_secondary_startup(void);
extern struct smp_operations armada_xp_smp_ops;
#endif

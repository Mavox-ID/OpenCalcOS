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
#ifndef __ASM_BLACKFIN_CPU_H
#define __ASM_BLACKFIN_CPU_H

#include <beep/percpu.h>

struct blackfin_cpudata {
	struct cpu cpu;
	unsigned int imemctl;
	unsigned int dmemctl;
#ifdef CONFIG_SMP
	struct task_struct *idle;
#endif
};

DECLARE_PER_CPU(struct blackfin_cpudata, cpu_data);

#endif

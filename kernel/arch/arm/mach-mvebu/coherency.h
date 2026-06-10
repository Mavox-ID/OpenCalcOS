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
#ifndef __MACH_370_XP_COHERENCY_H
#define __MACH_370_XP_COHERENCY_H

#ifdef CONFIG_SMP
int coherency_get_cpu_count(void);
#endif

int set_cpu_coherent(int cpu_id, int smp_group_id);
int coherency_init(void);

#endif	/* __MACH_370_XP_COHERENCY_H */

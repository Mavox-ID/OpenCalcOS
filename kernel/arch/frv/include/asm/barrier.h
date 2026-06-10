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
#ifndef _ASM_BARRIER_H
#define _ASM_BARRIER_H

#define nop()			asm volatile ("nop"::)

#define mb()			asm volatile ("membar" : : :"memory")
#define rmb()			asm volatile ("membar" : : :"memory")
#define wmb()			asm volatile ("membar" : : :"memory")
#define read_barrier_depends()	do { } while (0)

#define smp_mb()			barrier()
#define smp_rmb()			barrier()
#define smp_wmb()			barrier()
#define smp_read_barrier_depends()	do {} while(0)
#define set_mb(var, value) \
	do { var = (value); barrier(); } while (0)

#endif /* _ASM_BARRIER_H */

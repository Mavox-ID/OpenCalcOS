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
#ifndef __ASM_AVR32_BARRIER_H
#define __ASM_AVR32_BARRIER_H

#define nop()			asm volatile("nop")

#define mb()			asm volatile("" : : : "memory")
#define rmb()			mb()
#define wmb()			asm volatile("sync 0" : : : "memory")
#define read_barrier_depends()  do { } while(0)
#define set_mb(var, value)      do { var = value; mb(); } while(0)

#ifdef CONFIG_SMP
# error "The AVR32 port does not support SMP"
#else
# define smp_mb()		barrier()
# define smp_rmb()		barrier()
# define smp_wmb()		barrier()
# define smp_read_barrier_depends() do { } while(0)
#endif


#endif /* __ASM_AVR32_BARRIER_H */

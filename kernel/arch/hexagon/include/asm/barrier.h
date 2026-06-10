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

#define rmb()				barrier()
#define read_barrier_depends()		barrier()
#define wmb()				barrier()
#define mb()				barrier()
#define smp_rmb()			barrier()
#define smp_read_barrier_depends()	barrier()
#define smp_wmb()			barrier()
#define smp_mb()			barrier()
#define smp_mb__before_atomic_dec()	barrier()
#define smp_mb__after_atomic_dec()	barrier()
#define smp_mb__before_atomic_inc()	barrier()
#define smp_mb__after_atomic_inc()	barrier()

/*  Set a value and use a memory barrier.  Used by the scheduler somewhere.  */
#define set_mb(var, value) \
	do { var = value; mb(); } while (0)

#endif /* _ASM_BARRIER_H */

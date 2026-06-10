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
#ifndef __ASM_BARRIER_H
#define __ASM_BARRIER_H

/*
 * Force strict CPU ordering.
 * And yes, this is required on UP too when we're talking
 * to devices.
 */

static inline void mb(void)
{
#ifdef CONFIG_HAVE_MARCH_Z196_FEATURES
	/* Fast-BCR without checkpoint synchronization */
	asm volatile("bcr 14,0" : : : "memory");
#else
	asm volatile("bcr 15,0" : : : "memory");
#endif
}

#define rmb()				mb()
#define wmb()				mb()
#define read_barrier_depends()		do { } while(0)
#define smp_mb()			mb()
#define smp_rmb()			rmb()
#define smp_wmb()			wmb()
#define smp_read_barrier_depends()	read_barrier_depends()
#define smp_mb__before_clear_bit()	smp_mb()
#define smp_mb__after_clear_bit()	smp_mb()

#define set_mb(var, value)		do { var = value; mb(); } while (0)

#endif /* __ASM_BARRIER_H */

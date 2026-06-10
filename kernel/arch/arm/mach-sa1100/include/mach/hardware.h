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
#ifndef __ASM_ARCH_HARDWARE_H
#define __ASM_ARCH_HARDWARE_H


#define UNCACHEABLE_ADDR	0xfa050000


/*
 * SA1100 internal I/O mappings
 *
 * We have the following mapping:
 *      phys            virt
 *      80000000        f8000000
 *      90000000        fa000000
 *      a0000000        fc000000
 *      b0000000        fe000000
 */

#define VIO_BASE        0xf8000000	/* virtual start of IO space */
#define VIO_SHIFT       3		/* x = IO space shrink power */
#define PIO_START       0x80000000	/* physical start of IO space */

#define io_p2v( x )             \
   IOMEM( (((x)&0x00ffffff) | (((x)&0x30000000)>>VIO_SHIFT)) + VIO_BASE )
#define io_v2p( x )             \
   ( (((x)&0x00ffffff) | (((x)&(0x30000000>>VIO_SHIFT))<<VIO_SHIFT)) + PIO_START )

#define CPU_SA1110_A0	(0)
#define CPU_SA1110_B0	(4)
#define CPU_SA1110_B1	(5)
#define CPU_SA1110_B2	(6)
#define CPU_SA1110_B4	(8)

#define CPU_SA1100_ID	(0x4401a110)
#define CPU_SA1100_MASK	(0xfffffff0)
#define CPU_SA1110_ID	(0x6901b110)
#define CPU_SA1110_MASK	(0xfffffff0)

#define __MREG(x)	IOMEM(io_p2v(x))

#ifndef __ASSEMBLY__

#include <asm/cputype.h>

#define CPU_REVISION	(read_cpuid_id() & 15)

#define cpu_is_sa1100()	((read_cpuid_id() & CPU_SA1100_MASK) == CPU_SA1100_ID)
#define cpu_is_sa1110()	((read_cpuid_id() & CPU_SA1110_MASK) == CPU_SA1110_ID)

# define __REG(x)	(*((volatile unsigned long __iomem *)io_p2v(x)))
# define __PREG(x)	(io_v2p((unsigned long)&(x)))

static inline unsigned long get_clock_tick_rate(void)
{
	return 3686400;
}
#else

# define __REG(x)	io_p2v(x)
# define __PREG(x)	io_v2p(x)

#endif

#include "SA-1100.h"

#ifdef CONFIG_SA1101
#include "SA-1101.h"
#endif

#endif  /* _ASM_ARCH_HARDWARE_H */

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
#ifndef _ASM_ARCH_CPU_H
#define _ASM_ARCH_CPU_H

#include <mach/common.h>

struct davinci_id {
	u8	variant;	/* JTAG ID bits 31:28 */
	u16	part_no;	/* JTAG ID bits 27:12 */
	u16	manufacturer;	/* JTAG ID bits 11:1 */
	u32	cpu_id;
	char	*name;
};

/* Can use lower 16 bits of cpu id  for a variant when required */
#define	DAVINCI_CPU_ID_DM6446		0x64460000
#define	DAVINCI_CPU_ID_DM6467		0x64670000
#define	DAVINCI_CPU_ID_DM355		0x03550000
#define	DAVINCI_CPU_ID_DM365		0x03650000
#define	DAVINCI_CPU_ID_DA830		0x08300000
#define	DAVINCI_CPU_ID_DA850		0x08500000
#define	DAVINCI_CPU_ID_TNETV107X	0x0b8a0000

#define IS_DAVINCI_CPU(type, id)					\
static inline int is_davinci_ ##type(void)				\
{									\
	return (davinci_soc_info.cpu_id == (id));			\
}

IS_DAVINCI_CPU(dm644x, DAVINCI_CPU_ID_DM6446)
IS_DAVINCI_CPU(dm646x, DAVINCI_CPU_ID_DM6467)
IS_DAVINCI_CPU(dm355, DAVINCI_CPU_ID_DM355)
IS_DAVINCI_CPU(dm365, DAVINCI_CPU_ID_DM365)
IS_DAVINCI_CPU(da830, DAVINCI_CPU_ID_DA830)
IS_DAVINCI_CPU(da850, DAVINCI_CPU_ID_DA850)
IS_DAVINCI_CPU(tnetv107x, DAVINCI_CPU_ID_TNETV107X)

#ifdef CONFIG_ARCH_DAVINCI_DM644x
#define cpu_is_davinci_dm644x() is_davinci_dm644x()
#else
#define cpu_is_davinci_dm644x() 0
#endif

#ifdef CONFIG_ARCH_DAVINCI_DM646x
#define cpu_is_davinci_dm646x() is_davinci_dm646x()
#else
#define cpu_is_davinci_dm646x() 0
#endif

#ifdef CONFIG_ARCH_DAVINCI_DM355
#define cpu_is_davinci_dm355() is_davinci_dm355()
#else
#define cpu_is_davinci_dm355() 0
#endif

#ifdef CONFIG_ARCH_DAVINCI_DM365
#define cpu_is_davinci_dm365() is_davinci_dm365()
#else
#define cpu_is_davinci_dm365() 0
#endif

#ifdef CONFIG_ARCH_DAVINCI_DA830
#define cpu_is_davinci_da830() is_davinci_da830()
#else
#define cpu_is_davinci_da830() 0
#endif

#ifdef CONFIG_ARCH_DAVINCI_DA850
#define cpu_is_davinci_da850() is_davinci_da850()
#else
#define cpu_is_davinci_da850() 0
#endif

#ifdef CONFIG_ARCH_DAVINCI_TNETV107X
#define cpu_is_davinci_tnetv107x() is_davinci_tnetv107x()
#else
#define cpu_is_davinci_tnetv107x() 0
#endif

#endif

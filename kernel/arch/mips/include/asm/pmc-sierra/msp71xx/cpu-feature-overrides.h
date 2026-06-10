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
#ifndef __ASM_MACH_MSP71XX_CPU_FEATURE_OVERRIDES_H
#define __ASM_MACH_MSP71XX_CPU_FEATURE_OVERRIDES_H

#define cpu_has_mips16		1
#define cpu_has_dsp		1
/* #define cpu_has_dsp2		??? - do runtime detection */
#define cpu_has_mipsmt		1
#define cpu_has_fpu		0

#define cpu_has_mips32r1	0
#define cpu_has_mips32r2	1
#define cpu_has_mips64r1	0
#define cpu_has_mips64r2	0

#endif /* __ASM_MACH_MSP71XX_CPU_FEATURE_OVERRIDES_H */

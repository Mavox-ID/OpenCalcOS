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
#ifndef __ASM_CPU_SH3_FREQ_H
#define __ASM_CPU_SH3_FREQ_H

#ifdef CONFIG_CPU_SUBTYPE_SH7712
#define FRQCR			0xA415FF80
#else
#define FRQCR			0xffffff80
#endif

#define MIN_DIVISOR_NR		0
#define MAX_DIVISOR_NR		4

#define FRQCR_CKOEN	0x0100
#define FRQCR_PLLEN	0x0080
#define FRQCR_PSTBY	0x0040

#endif /* __ASM_CPU_SH3_FREQ_H */


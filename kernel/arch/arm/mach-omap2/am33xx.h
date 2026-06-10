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
#ifndef __ASM_ARCH_AM33XX_H
#define __ASM_ARCH_AM33XX_H

#define L4_SLOW_AM33XX_BASE	0x48000000

#define AM33XX_SCM_BASE		0x44E10000
#define AM33XX_CTRL_BASE	AM33XX_SCM_BASE
#define AM33XX_PRCM_BASE	0x44E00000
#define AM33XX_TAP_BASE		(AM33XX_CTRL_BASE + 0x3FC)

#endif /* __ASM_ARCH_AM33XX_H */

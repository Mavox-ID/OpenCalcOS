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
#ifndef _ASM_MACH_MIPS_MACH_GT64120_DEP_H
#define _ASM_MACH_MIPS_MACH_GT64120_DEP_H

#define MIPS_GT_BASE	0x1be00000

extern unsigned long _pcictrl_gt64120;
/*
 *   GT64120 config space base address
 */
#define GT64120_BASE	_pcictrl_gt64120

#endif /* _ASM_MACH_MIPS_MACH_GT64120_DEP_H */

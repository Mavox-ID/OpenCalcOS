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
#ifndef _MIPS_SEAD3INT_H
#define _MIPS_SEAD3INT_H

/* SEAD-3 GIC address space definitions. */
#define GIC_BASE_ADDR		0x1b1c0000
#define GIC_ADDRSPACE_SZ	(128 * 1024)

#define MIPS_GIC_IRQ_BASE	(MIPS_CPU_IRQ_BASE + 0)

#endif /* !(_MIPS_SEAD3INT_H) */

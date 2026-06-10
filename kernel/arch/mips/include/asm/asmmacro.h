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
#ifndef _ASM_ASMMACRO_H
#define _ASM_ASMMACRO_H

#include <asm/hazards.h>

#ifdef CONFIG_32BIT
#include <asm/asmmacro-32.h>
#endif
#ifdef CONFIG_64BIT
#include <asm/asmmacro-64.h>
#endif
#ifdef CONFIG_MIPS_MT_SMTC
#include <asm/mipsmtregs.h>
#endif

#ifdef CONFIG_MIPS_MT_SMTC
	.macro	local_irq_enable reg=t0
	mfc0	\reg, CP0_TCSTATUS
	ori	\reg, \reg, TCSTATUS_IXMT
	xori	\reg, \reg, TCSTATUS_IXMT
	mtc0	\reg, CP0_TCSTATUS
	_ehb
	.endm

	.macro	local_irq_disable reg=t0
	mfc0	\reg, CP0_TCSTATUS
	ori	\reg, \reg, TCSTATUS_IXMT
	mtc0	\reg, CP0_TCSTATUS
	_ehb
	.endm
#elif defined(CONFIG_CPU_MIPSR2)
	.macro	local_irq_enable reg=t0
	ei
	irq_enable_hazard
	.endm

	.macro	local_irq_disable reg=t0
	di
	irq_disable_hazard
	.endm
#else
	.macro	local_irq_enable reg=t0
	mfc0	\reg, CP0_STATUS
	ori	\reg, \reg, 1
	mtc0	\reg, CP0_STATUS
	irq_enable_hazard
	.endm

	.macro	local_irq_disable reg=t0
	mfc0	\reg, CP0_STATUS
	ori	\reg, \reg, 1
	xori	\reg, \reg, 1
	mtc0	\reg, CP0_STATUS
	irq_disable_hazard
	.endm
#endif /* CONFIG_MIPS_MT_SMTC */

/*
 * Temporary until all gas have MT ASE support
 */
	.macro	DMT	reg=0
	.word	0x41600bc1 | (\reg << 16)
	.endm

	.macro	EMT	reg=0
	.word	0x41600be1 | (\reg << 16)
	.endm

	.macro	DVPE	reg=0
	.word	0x41600001 | (\reg << 16)
	.endm

	.macro	EVPE	reg=0
	.word	0x41600021 | (\reg << 16)
	.endm

	.macro	MFTR	rt=0, rd=0, u=0, sel=0
	 .word	0x41000000 | (\rt << 16) | (\rd << 11) | (\u << 5) | (\sel)
	.endm

	.macro	MTTR	rt=0, rd=0, u=0, sel=0
	 .word	0x41800000 | (\rt << 16) | (\rd << 11) | (\u << 5) | (\sel)
	.endm

#endif /* _ASM_ASMMACRO_H */

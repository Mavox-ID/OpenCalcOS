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
#ifndef _MIPS_MALTAINT_H
#define _MIPS_MALTAINT_H

#define MIPS_GIC_IRQ_BASE	(MIPS_CPU_IRQ_BASE + 8)

/*
 * Interrupts 0..15 are used for Malta ISA compatible interrupts
 */
#define MALTA_INT_BASE		0

/* CPU interrupt offsets */
#define MIPSCPU_INT_SW0		0
#define MIPSCPU_INT_SW1		1
#define MIPSCPU_INT_MB0		2
#define MIPSCPU_INT_I8259A	MIPSCPU_INT_MB0
#define MIPSCPU_INT_MB1		3
#define MIPSCPU_INT_SMI		MIPSCPU_INT_MB1
#define MIPSCPU_INT_IPI0	MIPSCPU_INT_MB1	/* GIC IPI */
#define MIPSCPU_INT_MB2		4
#define MIPSCPU_INT_IPI1	MIPSCPU_INT_MB2	/* GIC IPI */
#define MIPSCPU_INT_MB3		5
#define MIPSCPU_INT_COREHI	MIPSCPU_INT_MB3
#define MIPSCPU_INT_MB4		6
#define MIPSCPU_INT_CORELO	MIPSCPU_INT_MB4

/*
 * Interrupts 64..127 are used for Soc-it Classic interrupts
 */
#define MSC01C_INT_BASE		64

/* SOC-it Classic interrupt offsets */
#define MSC01C_INT_TMR		0
#define MSC01C_INT_PCI		1

/*
 * Interrupts 64..127 are used for Soc-it EIC interrupts
 */
#define MSC01E_INT_BASE		64

/* SOC-it EIC interrupt offsets */
#define MSC01E_INT_SW0		1
#define MSC01E_INT_SW1		2
#define MSC01E_INT_MB0		3
#define MSC01E_INT_I8259A	MSC01E_INT_MB0
#define MSC01E_INT_MB1		4
#define MSC01E_INT_SMI		MSC01E_INT_MB1
#define MSC01E_INT_MB2		5
#define MSC01E_INT_MB3		6
#define MSC01E_INT_COREHI	MSC01E_INT_MB3
#define MSC01E_INT_MB4		7
#define MSC01E_INT_CORELO	MSC01E_INT_MB4
#define MSC01E_INT_TMR		8
#define MSC01E_INT_PCI		9
#define MSC01E_INT_PERFCTR	10
#define MSC01E_INT_CPUCTR	11

/* External Interrupts used for IPI */
#define GIC_IPI_EXT_INTR_RESCHED_VPE0	16
#define GIC_IPI_EXT_INTR_CALLFNC_VPE0	17
#define GIC_IPI_EXT_INTR_RESCHED_VPE1	18
#define GIC_IPI_EXT_INTR_CALLFNC_VPE1	19
#define GIC_IPI_EXT_INTR_RESCHED_VPE2	20
#define GIC_IPI_EXT_INTR_CALLFNC_VPE2	21
#define GIC_IPI_EXT_INTR_RESCHED_VPE3	22
#define GIC_IPI_EXT_INTR_CALLFNC_VPE3	23

#endif /* !(_MIPS_MALTAINT_H) */

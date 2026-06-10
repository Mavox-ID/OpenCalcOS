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
#ifndef __IRQS_H
#define __IRQS_H

/*
 * IOP80331 chipset interrupts
 */
#define IRQ_IOP33X_DMA0_EOT	0
#define IRQ_IOP33X_DMA0_EOC	1
#define IRQ_IOP33X_DMA1_EOT	2
#define IRQ_IOP33X_DMA1_EOC	3
#define IRQ_IOP33X_AA_EOT	6
#define IRQ_IOP33X_AA_EOC	7
#define IRQ_IOP33X_TIMER0	8
#define IRQ_IOP33X_TIMER1	9
#define IRQ_IOP33X_I2C_0	10
#define IRQ_IOP33X_I2C_1	11
#define IRQ_IOP33X_MSG		12
#define IRQ_IOP33X_MSGIBQ	13
#define IRQ_IOP33X_ATU_BIST	14
#define IRQ_IOP33X_PERFMON	15
#define IRQ_IOP33X_CORE_PMU	16
#define IRQ_IOP33X_XINT0	24
#define IRQ_IOP33X_XINT1	25
#define IRQ_IOP33X_XINT2	26
#define IRQ_IOP33X_XINT3	27
#define IRQ_IOP33X_XINT8	32
#define IRQ_IOP33X_XINT9	33
#define IRQ_IOP33X_XINT10	34
#define IRQ_IOP33X_XINT11	35
#define IRQ_IOP33X_XINT12	36
#define IRQ_IOP33X_XINT13	37
#define IRQ_IOP33X_XINT14	38
#define IRQ_IOP33X_XINT15	39
#define IRQ_IOP33X_UART0	51
#define IRQ_IOP33X_UART1	52
#define IRQ_IOP33X_PBIE		53
#define IRQ_IOP33X_ATU_CRW	54
#define IRQ_IOP33X_ATU_ERR	55
#define IRQ_IOP33X_MCU_ERR	56
#define IRQ_IOP33X_DMA0_ERR	57
#define IRQ_IOP33X_DMA1_ERR	58
#define IRQ_IOP33X_AA_ERR	60
#define IRQ_IOP33X_MSG_ERR	62
#define IRQ_IOP33X_HPI		63

#define NR_IRQS			64


#endif

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
#ifndef __ASM_ARCH_IRQS_H
#define __ASM_ARCH_IRQS_H

/*
 * MV78xx0 Low Interrupt Controller
 */
#define IRQ_MV78XX0_ERR		0
#define IRQ_MV78XX0_SPI		1
#define IRQ_MV78XX0_I2C_0	2
#define IRQ_MV78XX0_I2C_1	3
#define IRQ_MV78XX0_IDMA_0	4
#define IRQ_MV78XX0_IDMA_1	5
#define IRQ_MV78XX0_IDMA_2	6
#define IRQ_MV78XX0_IDMA_3	7
#define IRQ_MV78XX0_TIMER_0	8
#define IRQ_MV78XX0_TIMER_1	9
#define IRQ_MV78XX0_TIMER_2	10
#define IRQ_MV78XX0_TIMER_3	11
#define IRQ_MV78XX0_UART_0	12
#define IRQ_MV78XX0_UART_1	13
#define IRQ_MV78XX0_UART_2	14
#define IRQ_MV78XX0_UART_3	15
#define IRQ_MV78XX0_USB_0	16
#define IRQ_MV78XX0_USB_1	17
#define IRQ_MV78XX0_USB_2	18
#define IRQ_MV78XX0_CRYPTO	19
#define IRQ_MV78XX0_SDIO_0	20
#define IRQ_MV78XX0_SDIO_1	21
#define IRQ_MV78XX0_XOR_0	22
#define IRQ_MV78XX0_XOR_1	23
#define IRQ_MV78XX0_I2S_0	24
#define IRQ_MV78XX0_I2S_1	25
#define IRQ_MV78XX0_SATA	26
#define IRQ_MV78XX0_TDMI	27

/*
 * MV78xx0 High Interrupt Controller
 */
#define IRQ_MV78XX0_PCIE_00	32
#define IRQ_MV78XX0_PCIE_01	33
#define IRQ_MV78XX0_PCIE_02	34
#define IRQ_MV78XX0_PCIE_03	35
#define IRQ_MV78XX0_PCIE_10	36
#define IRQ_MV78XX0_PCIE_11	37
#define IRQ_MV78XX0_PCIE_12	38
#define IRQ_MV78XX0_PCIE_13	39
#define IRQ_MV78XX0_GE00_SUM	40
#define IRQ_MV78XX0_GE00_RX	41
#define IRQ_MV78XX0_GE00_TX	42
#define IRQ_MV78XX0_GE00_MISC	43
#define IRQ_MV78XX0_GE01_SUM	44
#define IRQ_MV78XX0_GE01_RX	45
#define IRQ_MV78XX0_GE01_TX	46
#define IRQ_MV78XX0_GE01_MISC	47
#define IRQ_MV78XX0_GE10_SUM	48
#define IRQ_MV78XX0_GE10_RX	49
#define IRQ_MV78XX0_GE10_TX	50
#define IRQ_MV78XX0_GE10_MISC	51
#define IRQ_MV78XX0_GE11_SUM	52
#define IRQ_MV78XX0_GE11_RX	53
#define IRQ_MV78XX0_GE11_TX	54
#define IRQ_MV78XX0_GE11_MISC	55
#define IRQ_MV78XX0_GPIO_0_7	56
#define IRQ_MV78XX0_GPIO_8_15	57
#define IRQ_MV78XX0_GPIO_16_23	58
#define IRQ_MV78XX0_GPIO_24_31	59
#define IRQ_MV78XX0_DB_IN	60
#define IRQ_MV78XX0_DB_OUT	61

/*
 * MV78xx0 Error Interrupt Controller
 */
#define IRQ_MV78XX0_GE_ERR	70

/*
 * MV78XX0 General Purpose Pins
 */
#define IRQ_MV78XX0_GPIO_START	96
#define NR_GPIO_IRQS		32

#define NR_IRQS			(IRQ_MV78XX0_GPIO_START + NR_GPIO_IRQS)


#endif

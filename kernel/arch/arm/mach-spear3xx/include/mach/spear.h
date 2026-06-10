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
#ifndef __MACH_SPEAR3XX_H
#define __MACH_SPEAR3XX_H

#include <asm/memory.h>

/* ICM1 - Low speed connection */
#define SPEAR3XX_ICM1_2_BASE		UL(0xD0000000)
#define VA_SPEAR3XX_ICM1_2_BASE		UL(0xFD000000)
#define SPEAR3XX_ICM1_UART_BASE		UL(0xD0000000)
#define VA_SPEAR3XX_ICM1_UART_BASE	(VA_SPEAR3XX_ICM1_2_BASE | SPEAR3XX_ICM1_UART_BASE)
#define SPEAR3XX_ICM1_SSP_BASE		UL(0xD0100000)

/* ML1 - Multi Layer CPU Subsystem */
#define SPEAR3XX_ICM3_ML1_2_BASE	UL(0xF0000000)
#define VA_SPEAR6XX_ML_CPU_BASE		UL(0xF0000000)

/* ICM3 - Basic Subsystem */
#define SPEAR3XX_ICM3_SMI_CTRL_BASE	UL(0xFC000000)
#define VA_SPEAR3XX_ICM3_SMI_CTRL_BASE	UL(0xFC000000)
#define SPEAR3XX_ICM3_DMA_BASE		UL(0xFC400000)
#define SPEAR3XX_ICM3_SYS_CTRL_BASE	UL(0xFCA00000)
#define VA_SPEAR3XX_ICM3_SYS_CTRL_BASE	(VA_SPEAR3XX_ICM3_SMI_CTRL_BASE | SPEAR3XX_ICM3_SYS_CTRL_BASE)
#define SPEAR3XX_ICM3_MISC_REG_BASE	UL(0xFCA80000)
#define VA_SPEAR3XX_ICM3_MISC_REG_BASE	(VA_SPEAR3XX_ICM3_SMI_CTRL_BASE | SPEAR3XX_ICM3_MISC_REG_BASE)

/* Debug uart for beep, will be used for debug and uncompress messages */
#define SPEAR_DBG_UART_BASE		SPEAR3XX_ICM1_UART_BASE
#define VA_SPEAR_DBG_UART_BASE		VA_SPEAR3XX_ICM1_UART_BASE

/* Sysctl base for spear platform */
#define SPEAR_SYS_CTRL_BASE		SPEAR3XX_ICM3_SYS_CTRL_BASE
#define VA_SPEAR_SYS_CTRL_BASE		VA_SPEAR3XX_ICM3_SYS_CTRL_BASE

/* SPEAr320 Macros */
#define SPEAR320_SOC_CONFIG_BASE	UL(0xB3000000)
#define VA_SPEAR320_SOC_CONFIG_BASE	UL(0xFE000000)
#define SPEAR320_CONTROL_REG		IOMEM(VA_SPEAR320_SOC_CONFIG_BASE)
#define SPEAR320_EXT_CTRL_REG		IOMEM(VA_SPEAR320_SOC_CONFIG_BASE + 0x0018)
	#define SPEAR320_UARTX_PCLK_MASK		0x1
	#define SPEAR320_UART2_PCLK_SHIFT		8
	#define SPEAR320_UART3_PCLK_SHIFT		9
	#define SPEAR320_UART4_PCLK_SHIFT		10
	#define SPEAR320_UART5_PCLK_SHIFT		11
	#define SPEAR320_UART6_PCLK_SHIFT		12
	#define SPEAR320_RS485_PCLK_SHIFT		13

#endif /* __MACH_SPEAR3XX_H */

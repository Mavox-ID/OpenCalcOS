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
#ifndef __MACH_SPEAR13XX_H
#define __MACH_SPEAR13XX_H

#include <asm/memory.h>

#define PERIP_GRP2_BASE				UL(0xB3000000)
#define VA_PERIP_GRP2_BASE			IOMEM(0xFE000000)
#define MCIF_SDHCI_BASE				UL(0xB3000000)
#define SYSRAM0_BASE				UL(0xB3800000)
#define VA_SYSRAM0_BASE				IOMEM(0xFE800000)
#define SYS_LOCATION				(VA_SYSRAM0_BASE + 0x600)

#define PERIP_GRP1_BASE				UL(0xE0000000)
#define VA_PERIP_GRP1_BASE			IOMEM(0xFD000000)
#define UART_BASE				UL(0xE0000000)
#define VA_UART_BASE				IOMEM(0xFD000000)
#define SSP_BASE				UL(0xE0100000)
#define MISC_BASE				UL(0xE0700000)
#define VA_MISC_BASE				IOMEM(0xFD700000)

#define A9SM_AND_MPMC_BASE			UL(0xEC000000)
#define VA_A9SM_AND_MPMC_BASE			IOMEM(0xFC000000)

/* A9SM peripheral offsets */
#define A9SM_PERIP_BASE				UL(0xEC800000)
#define VA_A9SM_PERIP_BASE			IOMEM(0xFC800000)
#define VA_SCU_BASE				(VA_A9SM_PERIP_BASE + 0x00)

#define L2CC_BASE				UL(0xED000000)
#define VA_L2CC_BASE				IOMEM(UL(0xFB000000))

/* others */
#define DMAC0_BASE				UL(0xEA800000)
#define DMAC1_BASE				UL(0xEB000000)
#define MCIF_CF_BASE				UL(0xB2800000)

/* Debug uart for beep, will be used for debug and uncompress messages */
#define SPEAR_DBG_UART_BASE			UART_BASE
#define VA_SPEAR_DBG_UART_BASE			VA_UART_BASE

#endif /* __MACH_SPEAR13XX_H */

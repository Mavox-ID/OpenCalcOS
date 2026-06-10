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
#ifndef __ASM_ARCH_OMAP7XX_H
#define __ASM_ARCH_OMAP7XX_H

/*
 * ----------------------------------------------------------------------------
 * Base addresses
 * ----------------------------------------------------------------------------
 */

/* Syntax: XX_BASE = Virtual base address, XX_START = Physical base address */

#define OMAP7XX_DSP_BASE	0xE0000000
#define OMAP7XX_DSP_SIZE	0x50000
#define OMAP7XX_DSP_START	0xE0000000

#define OMAP7XX_DSPREG_BASE	0xE1000000
#define OMAP7XX_DSPREG_SIZE	SZ_128K
#define OMAP7XX_DSPREG_START	0xE1000000

#define OMAP7XX_SPI1_BASE	0xfffc0800
#define OMAP7XX_SPI2_BASE	0xfffc1000

/*
 * ----------------------------------------------------------------------------
 * OMAP7XX specific configuration registers
 * ----------------------------------------------------------------------------
 */
#define OMAP7XX_CONFIG_BASE	0xfffe1000
#define OMAP7XX_IO_CONF_0	0xfffe1070
#define OMAP7XX_IO_CONF_1	0xfffe1074
#define OMAP7XX_IO_CONF_2	0xfffe1078
#define OMAP7XX_IO_CONF_3	0xfffe107c
#define OMAP7XX_IO_CONF_4	0xfffe1080
#define OMAP7XX_IO_CONF_5	0xfffe1084
#define OMAP7XX_IO_CONF_6	0xfffe1088
#define OMAP7XX_IO_CONF_7	0xfffe108c
#define OMAP7XX_IO_CONF_8	0xfffe1090
#define OMAP7XX_IO_CONF_9	0xfffe1094
#define OMAP7XX_IO_CONF_10	0xfffe1098
#define OMAP7XX_IO_CONF_11	0xfffe109c
#define OMAP7XX_IO_CONF_12	0xfffe10a0
#define OMAP7XX_IO_CONF_13	0xfffe10a4

#define OMAP7XX_MODE_1		0xfffe1010
#define OMAP7XX_MODE_2		0xfffe1014

/* CSMI specials: in terms of base + offset */
#define OMAP7XX_MODE2_OFFSET	0x14

/*
 * ----------------------------------------------------------------------------
 * OMAP7XX traffic controller configuration registers
 * ----------------------------------------------------------------------------
 */
#define OMAP7XX_FLASH_CFG_0	0xfffecc10
#define OMAP7XX_FLASH_ACFG_0	0xfffecc50
#define OMAP7XX_FLASH_CFG_1	0xfffecc14
#define OMAP7XX_FLASH_ACFG_1	0xfffecc54

/*
 * ----------------------------------------------------------------------------
 * OMAP7XX DSP control registers
 * ----------------------------------------------------------------------------
 */
#define OMAP7XX_ICR_BASE	0xfffbb800
#define OMAP7XX_DSP_M_CTL	0xfffbb804
#define OMAP7XX_DSP_MMU_BASE	0xfffed200

/*
 * ----------------------------------------------------------------------------
 * OMAP7XX PCC_UPLD configuration registers
 * ----------------------------------------------------------------------------
 */
#define OMAP7XX_PCC_UPLD_CTRL_BASE	(0xfffe0900)
#define OMAP7XX_PCC_UPLD_CTRL		(OMAP7XX_PCC_UPLD_CTRL_BASE + 0x00)

#endif /*  __ASM_ARCH_OMAP7XX_H */


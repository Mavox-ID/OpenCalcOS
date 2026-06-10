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
#ifndef CSB726_H
#define CSB726_H

#define CSB726_GPIO_IRQ_LAN	52
#define CSB726_GPIO_IRQ_SM501	53
#define CSB726_GPIO_MMC_DETECT	100
#define CSB726_GPIO_MMC_RO	101

#define CSB726_FLASH_SIZE	(64 * 1024 * 1024)
#define CSB726_FLASH_uMON	(8 * 1024 * 1024)

#define CSB726_IRQ_LAN		PXA_GPIO_TO_IRQ(CSB726_GPIO_IRQ_LAN)
#define CSB726_IRQ_SM501	PXA_GPIO_TO_IRQ(CSB726_GPIO_IRQ_SM501)

#endif


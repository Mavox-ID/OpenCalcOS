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
#define LUBBOCK_ETH_PHYS	PXA_CS3_PHYS

#define LUBBOCK_FPGA_PHYS	PXA_CS2_PHYS
#define LUBBOCK_FPGA_VIRT	(0xf0000000)
#define LUB_P2V(x)		((x) - LUBBOCK_FPGA_PHYS + LUBBOCK_FPGA_VIRT)
#define LUB_V2P(x)		((x) - LUBBOCK_FPGA_VIRT + LUBBOCK_FPGA_PHYS)

#ifndef __ASSEMBLY__
#  define __LUB_REG(x)		(*((volatile unsigned long *)LUB_P2V(x)))
#else
#  define __LUB_REG(x)		LUB_P2V(x)
#endif

/* FPGA register virtual addresses */
#define LUB_WHOAMI		__LUB_REG(LUBBOCK_FPGA_PHYS + 0x000)
#define LUB_DISC_BLNK_LED	__LUB_REG(LUBBOCK_FPGA_PHYS + 0x040)
#define LUB_CONF_SWITCHES	__LUB_REG(LUBBOCK_FPGA_PHYS + 0x050)
#define LUB_USER_SWITCHES	__LUB_REG(LUBBOCK_FPGA_PHYS + 0x060)
#define LUB_MISC_WR		__LUB_REG(LUBBOCK_FPGA_PHYS + 0x080)
#define LUB_MISC_RD		__LUB_REG(LUBBOCK_FPGA_PHYS + 0x090)
#define LUB_IRQ_MASK_EN		__LUB_REG(LUBBOCK_FPGA_PHYS + 0x0c0)
#define LUB_IRQ_SET_CLR		__LUB_REG(LUBBOCK_FPGA_PHYS + 0x0d0)
#define LUB_GP			__LUB_REG(LUBBOCK_FPGA_PHYS + 0x100)

/* Board specific IRQs */
#define LUBBOCK_IRQ(x)		(IRQ_BOARD_START + (x))
#define LUBBOCK_SD_IRQ		LUBBOCK_IRQ(0)
#define LUBBOCK_SA1111_IRQ	LUBBOCK_IRQ(1)
#define LUBBOCK_USB_IRQ		LUBBOCK_IRQ(2)  /* usb connect */
#define LUBBOCK_ETH_IRQ		LUBBOCK_IRQ(3)
#define LUBBOCK_UCB1400_IRQ	LUBBOCK_IRQ(4)
#define LUBBOCK_BB_IRQ		LUBBOCK_IRQ(5)
#define LUBBOCK_USB_DISC_IRQ	LUBBOCK_IRQ(6)  /* usb disconnect */
#define LUBBOCK_LAST_IRQ	LUBBOCK_IRQ(6)

#define LUBBOCK_SA1111_IRQ_BASE	(IRQ_BOARD_START + 16)
#define LUBBOCK_NR_IRQS		(IRQ_BOARD_START + 16 + 55)

#ifndef __ASSEMBLY__
extern void lubbock_set_misc_wr(unsigned int mask, unsigned int set);
#endif

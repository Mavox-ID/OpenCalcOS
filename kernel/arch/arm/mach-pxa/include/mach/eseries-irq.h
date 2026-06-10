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
#define ANGELX_IRQ_BASE (IRQ_BOARD_START+8)
#define IRQ_ANGELX(n) (ANGELX_IRQ_BASE + (n))

#define ANGELX_RDY0_IRQ IRQ_ANGELX(0)
#define ANGELX_ST0_IRQ  IRQ_ANGELX(1)
#define ANGELX_CD0_IRQ  IRQ_ANGELX(2)
#define ANGELX_RDY1_IRQ IRQ_ANGELX(3)
#define ANGELX_ST1_IRQ  IRQ_ANGELX(4)
#define ANGELX_CD1_IRQ  IRQ_ANGELX(5)

#define TMIO_IRQ_BASE (IRQ_BOARD_START+0)
#define IRQ_TMIO(n) (TMIO_IRQ_BASE + (n))

#define TMIO_SD_IRQ     IRQ_TMIO(1)
#define TMIO_USB_IRQ    IRQ_TMIO(2)

#define ESERIES_NR_IRQS	(IRQ_BOARD_START + 16)

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
#ifndef __PLAT_S3C64XX_REGS_MODEM_H
#define __PLAT_S3C64XX_REGS_MODEM_H __FILE__

#define S3C64XX_MODEMREG(x)	(S3C64XX_VA_MODEM + (x))

#define S3C64XX_MODEM_INT2AP			S3C64XX_MODEMREG(0x0)
#define S3C64XX_MODEM_INT2MODEM			S3C64XX_MODEMREG(0x4)
#define S3C64XX_MODEM_MIFCON			S3C64XX_MODEMREG(0x8)
#define S3C64XX_MODEM_MIFPCON			S3C64XX_MODEMREG(0xC)
#define S3C64XX_MODEM_INTCLR			S3C64XX_MODEMREG(0x10)
#define S3C64XX_MODEM_DMA_TXADDR		S3C64XX_MODEMREG(0x14)
#define S3C64XX_MODEM_DMA_RXADDR		S3C64XX_MODEMREG(0x18)

#define MIFPCON_INT2M_LEVEL			(1 << 4)
#define MIFPCON_LCD_BYPASS			(1 << 3)

#endif /* __PLAT_S3C64XX_REGS_MODEM_H */

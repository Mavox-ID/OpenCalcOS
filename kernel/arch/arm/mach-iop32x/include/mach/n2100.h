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
#ifndef __N2100_H
#define __N2100_H

#define N2100_UART		0xfe800000	/* UART */

#define N2100_COPY_BUTTON	IOP3XX_GPIO_LINE(0)
#define N2100_PCA9532_RESET	IOP3XX_GPIO_LINE(2)
#define N2100_RESET_BUTTON	IOP3XX_GPIO_LINE(3)
#define N2100_HARDWARE_RESET	IOP3XX_GPIO_LINE(4)
#define N2100_POWER_BUTTON	IOP3XX_GPIO_LINE(5)


#endif

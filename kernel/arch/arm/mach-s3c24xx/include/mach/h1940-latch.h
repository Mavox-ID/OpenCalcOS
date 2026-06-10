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
#ifndef __ASM_ARCH_H1940_LATCH_H
#define __ASM_ARCH_H1940_LATCH_H

#include <asm/gpio.h>

#define H1940_LATCH_GPIO(x)		(S3C_GPIO_END + (x))

/* SD layer latch */

#define H1940_LATCH_LCD_P0		H1940_LATCH_GPIO(0)
#define H1940_LATCH_LCD_P1		H1940_LATCH_GPIO(1)
#define H1940_LATCH_LCD_P2		H1940_LATCH_GPIO(2)
#define H1940_LATCH_LCD_P3		H1940_LATCH_GPIO(3)
#define H1940_LATCH_MAX1698_nSHUTDOWN	H1940_LATCH_GPIO(4)
#define H1940_LATCH_LED_RED		H1940_LATCH_GPIO(5)
#define H1940_LATCH_SDQ7		H1940_LATCH_GPIO(6)
#define H1940_LATCH_USB_DP		H1940_LATCH_GPIO(7)

/* CPU layer latch */

#define H1940_LATCH_UDA_POWER		H1940_LATCH_GPIO(8)
#define H1940_LATCH_AUDIO_POWER		H1940_LATCH_GPIO(9)
#define H1940_LATCH_SM803_ENABLE	H1940_LATCH_GPIO(10)
#define H1940_LATCH_LCD_P4		H1940_LATCH_GPIO(11)
#define H1940_LATCH_SD_POWER		H1940_LATCH_GPIO(12)
#define H1940_LATCH_BLUETOOTH_POWER	H1940_LATCH_GPIO(13)
#define H1940_LATCH_LED_GREEN		H1940_LATCH_GPIO(14)
#define H1940_LATCH_LED_FLASH		H1940_LATCH_GPIO(15)

#endif /* __ASM_ARCH_H1940_LATCH_H */

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
#ifndef ASM_ARCH_ZIPIT2_H
#define ASM_ARCH_ZIPIT2_H

/* LEDs */
#define	GPIO10_ZIPITZ2_LED_WIFI		10
#define	GPIO85_ZIPITZ2_LED_CHARGED	85
#define	GPIO83_ZIPITZ2_LED_CHARGING	83

/* SD/MMC */
#define	GPIO96_ZIPITZ2_SD_DETECT	96

/* GPIO Buttons */
#define	GPIO1_ZIPITZ2_POWER_BUTTON	1
#define	GPIO98_ZIPITZ2_LID_BUTTON	98

/* Libertas GSPI8686 WiFi */
#define	GPIO14_ZIPITZ2_WIFI_POWER	14
#define	GPIO24_ZIPITZ2_WIFI_CS		24
#define	GPIO36_ZIPITZ2_WIFI_IRQ		36

/* LCD */
#define	GPIO19_ZIPITZ2_LCD_RESET	19
#define	GPIO88_ZIPITZ2_LCD_CS		88

/* MISC GPIOs */
#define	GPIO0_ZIPITZ2_AC_DETECT		0
#define GPIO37_ZIPITZ2_HEADSET_DETECT	37

#endif

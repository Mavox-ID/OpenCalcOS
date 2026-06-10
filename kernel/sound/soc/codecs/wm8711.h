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
#ifndef _WM8711_H
#define _WM8711_H

/* WM8711 register space */

#define WM8711_LOUT1V   0x02
#define WM8711_ROUT1V   0x03
#define WM8711_APANA    0x04
#define WM8711_APDIGI   0x05
#define WM8711_PWR      0x06
#define WM8711_IFACE    0x07
#define WM8711_SRATE    0x08
#define WM8711_ACTIVE   0x09
#define WM8711_RESET	0x0f

#define WM8711_CACHEREGNUM 	8

#define WM8711_SYSCLK	0
#define WM8711_DAI		0

struct wm8711_setup_data {
	unsigned short i2c_address;
};

#endif

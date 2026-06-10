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
#ifndef _MAX9850_H
#define _MAX9850_H

#define MAX9850_STATUSA			0x00
#define MAX9850_STATUSB			0x01
#define MAX9850_VOLUME			0x02
#define MAX9850_GENERAL_PURPOSE		0x03
#define MAX9850_INTERRUPT		0x04
#define MAX9850_ENABLE			0x05
#define MAX9850_CLOCK			0x06
#define MAX9850_CHARGE_PUMP		0x07
#define MAX9850_LRCLK_MSB		0x08
#define MAX9850_LRCLK_LSB		0x09
#define MAX9850_DIGITAL_AUDIO		0x0a

#define MAX9850_CACHEREGNUM 11

/* MAX9850_DIGITAL_AUDIO */
#define MAX9850_MASTER			(1<<7)
#define MAX9850_INV			(1<<6)
#define MAX9850_BCINV			(1<<5)
#define MAX9850_DLY			(1<<3)
#define MAX9850_RTJ			(1<<2)

#endif

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
#ifndef __ISINK_LP8788_H__
#define __ISINK_LP8788_H__

/* register address */
#define LP8788_ISINK_CTRL		0x99
#define LP8788_ISINK12_IOUT		0x9A
#define LP8788_ISINK3_IOUT		0x9B
#define LP8788_ISINK1_PWM		0x9C
#define LP8788_ISINK2_PWM		0x9D
#define LP8788_ISINK3_PWM		0x9E

/* mask bits */
#define LP8788_ISINK1_IOUT_M		0x0F	/* Addr 9Ah */
#define LP8788_ISINK2_IOUT_M		0xF0
#define LP8788_ISINK3_IOUT_M		0x0F	/* Addr 9Bh */

/* 6 bits used for PWM code : Addr 9C ~ 9Eh */
#define LP8788_ISINK_MAX_PWM		63
#define LP8788_ISINK_SCALE_OFFSET	3

static const u8 lp8788_iout_addr[] = {
	LP8788_ISINK12_IOUT,
	LP8788_ISINK12_IOUT,
	LP8788_ISINK3_IOUT,
};

static const u8 lp8788_iout_mask[] = {
	LP8788_ISINK1_IOUT_M,
	LP8788_ISINK2_IOUT_M,
	LP8788_ISINK3_IOUT_M,
};

static const u8 lp8788_pwm_addr[] = {
	LP8788_ISINK1_PWM,
	LP8788_ISINK2_PWM,
	LP8788_ISINK3_PWM,
};

#endif

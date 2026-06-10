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
#ifndef S3C24XXI2S_H_
#define S3C24XXI2S_H_

/* clock sources */
#define S3C24XX_CLKSRC_PCLK 0
#define S3C24XX_CLKSRC_MPLL 1

/* Clock dividers */
#define S3C24XX_DIV_MCLK	0
#define S3C24XX_DIV_BCLK	1
#define S3C24XX_DIV_PRESCALER	2

/* prescaler */
#define S3C24XX_PRESCALE(a,b) \
	(((a - 1) << S3C2410_IISPSR_INTSHIFT) | ((b - 1) << S3C2410_IISPSR_EXTSHFIT))

u32 s3c24xx_i2s_get_clockrate(void);

#endif /*S3C24XXI2S_H_*/

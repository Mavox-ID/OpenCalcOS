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
#ifndef __SND_SOC_S3C24XX_S3C2412_I2S_H
#define __SND_SOC_S3C24XX_S3C2412_I2S_H __FILE__

#include "s3c-i2s-v2.h"

#define S3C2412_DIV_BCLK	S3C_I2SV2_DIV_BCLK
#define S3C2412_DIV_RCLK	S3C_I2SV2_DIV_RCLK
#define S3C2412_DIV_PRESCALER	S3C_I2SV2_DIV_PRESCALER

#define S3C2412_CLKSRC_PCLK	S3C_I2SV2_CLKSRC_PCLK
#define S3C2412_CLKSRC_I2SCLK	S3C_I2SV2_CLKSRC_AUDIOBUS

#endif /* __SND_SOC_S3C24XX_S3C2412_I2S_H */

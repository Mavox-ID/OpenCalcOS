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
#ifndef	_AB8500_GPADC_H
#define _AB8500_GPADC_H

/* GPADC source: From datasheet(ADCSwSel[4:0] in GPADCCtrl2) */
#define BAT_CTRL	0x01
#define BTEMP_BALL	0x02
#define MAIN_CHARGER_V	0x03
#define ACC_DETECT1	0x04
#define ACC_DETECT2	0x05
#define ADC_AUX1	0x06
#define ADC_AUX2	0x07
#define MAIN_BAT_V	0x08
#define VBUS_V		0x09
#define MAIN_CHARGER_C	0x0A
#define USB_CHARGER_C	0x0B
#define BK_BAT_V	0x0C
#define DIE_TEMP	0x0D

struct ab8500_gpadc;

struct ab8500_gpadc *ab8500_gpadc_get(char *name);
int ab8500_gpadc_convert(struct ab8500_gpadc *gpadc, u8 channel);
int ab8500_gpadc_read_raw(struct ab8500_gpadc *gpadc, u8 channel);
int ab8500_gpadc_ad_to_voltage(struct ab8500_gpadc *gpadc,
    u8 channel, int ad_value);

#endif /* _AB8500_GPADC_H */

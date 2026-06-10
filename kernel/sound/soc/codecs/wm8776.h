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
#ifndef _WM8776_H
#define _WM8776_H

/* Registers */

#define WM8776_HPLVOL    0x00
#define WM8776_HPRVOL    0x01
#define WM8776_HPMASTER  0x02
#define WM8776_DACLVOL   0x03
#define WM8776_DACRVOL   0x04
#define WM8776_DACMASTER 0x05
#define WM8776_PHASESWAP 0x06
#define WM8776_DACCTRL1  0x07
#define WM8776_DACMUTE   0x08
#define WM8776_DACCTRL2  0x09
#define WM8776_DACIFCTRL 0x0a
#define WM8776_ADCIFCTRL 0x0b
#define WM8776_MSTRCTRL  0x0c
#define WM8776_PWRDOWN   0x0d
#define WM8776_ADCLVOL   0x0e
#define WM8776_ADCRVOL   0x0f
#define WM8776_ALCCTRL1  0x10
#define WM8776_ALCCTRL2  0x11
#define WM8776_ALCCTRL3  0x12
#define WM8776_NOISEGATE 0x13
#define WM8776_LIMITER   0x14
#define WM8776_ADCMUX    0x15
#define WM8776_OUTMUX    0x16
#define WM8776_RESET     0x17

#define WM8776_CACHEREGNUM 0x17

#define WM8776_DAI_DAC 0
#define WM8776_DAI_ADC 1

#endif

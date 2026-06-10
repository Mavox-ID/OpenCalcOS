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
/* HP Jornada 7xx microprocessor commands */
#define GETBATTERYDATA		0xc0
#define GETSCANKEYCODE		0x90
#define GETTOUCHSAMPLES		0xa0
#define GETCONTRAST		0xD0
#define SETCONTRAST		0xD1
#define GETBRIGHTNESS		0xD2
#define SETBRIGHTNESS		0xD3
#define CONTRASTOFF		0xD8
#define BRIGHTNESSOFF		0xD9
#define PWMOFF			0xDF
#define TXDUMMY			0x11
#define ERRORCODE		0x00

extern void jornada_ssp_start(void);
extern void jornada_ssp_end(void);
extern int jornada_ssp_inout(u8 byte);
extern int jornada_ssp_byte(u8 byte);

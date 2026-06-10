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
#define BYTE							unsigned char
#define WORD							unsigned int
#define rByteAMD(cs, reg)					cs->readisac(cs, reg)
#define wByteAMD(cs, reg, val)					cs->writeisac(cs, reg, val)
#define rWordAMD(cs, reg)					ReadWordAmd7930(cs, reg)
#define wWordAMD(cs, reg, val)					WriteWordAmd7930(cs, reg, val)
#define HIBYTE(w)						((unsigned char)((w & 0xff00) / 256))
#define LOBYTE(w)						((unsigned char)(w & 0x00ff))

#define AmdIrqOff(cs)						cs->dc.amd7930.setIrqMask(cs, 0)
#define AmdIrqOn(cs)						cs->dc.amd7930.setIrqMask(cs, 1)

#define AMD_CR		0x00
#define AMD_DR		0x01


#define DBUSY_TIMER_VALUE 80

extern void Amd7930_interrupt(struct IsdnCardState *, unsigned char);
extern void Amd7930_init(struct IsdnCardState *);
extern void setup_Amd7930(struct IsdnCardState *);

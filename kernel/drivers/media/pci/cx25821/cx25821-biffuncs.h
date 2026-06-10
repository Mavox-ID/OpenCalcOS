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
#ifndef _BITFUNCS_H
#define _BITFUNCS_H

#define SetBit(Bit)  (1 << Bit)

static inline u8 getBit(u32 sample, u8 index)
{
	return (u8) ((sample >> index) & 1);
}

static inline u32 clearBitAtPos(u32 value, u8 bit)
{
	return value & ~(1 << bit);
}

static inline u32 setBitAtPos(u32 sample, u8 bit)
{
	sample |= (1 << bit);
	return sample;

}

#endif

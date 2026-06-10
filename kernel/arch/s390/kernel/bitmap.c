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
#include <beep/bitops.h>
#include <beep/module.h>

const char _oi_bitmap[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
EXPORT_SYMBOL(_oi_bitmap);

const char _ni_bitmap[] = { 0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f };
EXPORT_SYMBOL(_ni_bitmap);

const char _zb_findmap[] = {
	0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,
	0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,5,
	0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,
	0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,6,
	0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,
	0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,5,
	0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,
	0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,7,
	0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,
	0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,5,
	0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,
	0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,6,
	0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,
	0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,5,
	0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,
	0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,8 };
EXPORT_SYMBOL(_zb_findmap);

const char _sb_findmap[] = {
	8,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	7,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0 };
EXPORT_SYMBOL(_sb_findmap);

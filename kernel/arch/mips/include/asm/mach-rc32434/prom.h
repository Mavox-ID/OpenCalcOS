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
#define PROM_ENTRY(x)		(0xbfc00000 + ((x) * 8))

#define SR_NMI			0x00180000
#define SERIAL_SPEED_ENTRY	0x00000001

#define FREQ_TAG		"HZ="
#define KMAC_TAG		"kmac="
#define MEM_TAG			"mem="
#define BOARD_TAG		"board="

#define BOARD_RB532		"500"
#define BOARD_RB532A		"500r5"

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
#define PVC_REG_100		KSEG1ADDR(0x1c820000)
#define PVC_DATA_SHIFT_100	0
#define PVC_DATA_M_100		0xFF
#define PVC_E_100		(1 << 8)
#define PVC_RW_100		(1 << 9)
#define PVC_RS_100		(1 << 10)

/* Lasat 200 */
#define PVC_REG_200		KSEG1ADDR(0x11000000)
#define PVC_DATA_SHIFT_200	24
#define PVC_DATA_M_200		(0xFF << PVC_DATA_SHIFT_200)
#define PVC_E_200		(1 << 16)
#define PVC_RW_200		(1 << 17)
#define PVC_RS_200		(1 << 18)

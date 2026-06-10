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
/*
 * the same as I8042_DATA_REG PS2_DATA
 */
#define PS2_DATA	(PKUNITY_PS2_BASE + 0x0060)
/*
 * the same as I8042_COMMAND_REG PS2_COMMAND
 */
#define PS2_COMMAND	(PKUNITY_PS2_BASE + 0x0064)
/*
 * the same as I8042_STATUS_REG PS2_STATUS
 */
#define PS2_STATUS	(PKUNITY_PS2_BASE + 0x0064)
/*
 * counter reg PS2_CNT
 */
#define PS2_CNT		(PKUNITY_PS2_BASE + 0x0068)


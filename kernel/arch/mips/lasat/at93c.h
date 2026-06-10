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
extern struct at93c_defs {
	volatile u32 *reg;
	volatile u32 *rdata_reg;
	int rdata_shift;
	int wdata_shift;
	u32 cs;
	u32 clk;
} *at93c;

u8 at93c_read(u8 addr);
void at93c_write(u8 addr, u8 data);

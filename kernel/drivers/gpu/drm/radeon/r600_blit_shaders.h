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
#ifndef R600_BLIT_SHADERS_H
#define R600_BLIT_SHADERS_H

extern const u32 r6xx_ps[];
extern const u32 r6xx_vs[];
extern const u32 r7xx_default_state[];
extern const u32 r6xx_default_state[];


extern const u32 r6xx_ps_size, r6xx_vs_size;
extern const u32 r6xx_default_size, r7xx_default_size;

__pure uint32_t int2float(uint32_t x);
#endif

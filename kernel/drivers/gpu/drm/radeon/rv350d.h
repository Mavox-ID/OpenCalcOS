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
#ifndef __RV350D_H__
#define __RV350D_H__

/* RV350, RV380 registers */
/* #define R_00000D_SCLK_CNTL                           0x00000D */
#define   S_00000D_FORCE_VAP(x)                        (((x) & 0x1) << 21)
#define   G_00000D_FORCE_VAP(x)                        (((x) >> 21) & 0x1)
#define   C_00000D_FORCE_VAP                           0xFFDFFFFF
#define   S_00000D_FORCE_SR(x)                         (((x) & 0x1) << 25)
#define   G_00000D_FORCE_SR(x)                         (((x) >> 25) & 0x1)
#define   C_00000D_FORCE_SR                            0xFDFFFFFF
#define   S_00000D_FORCE_PX(x)                         (((x) & 0x1) << 26)
#define   G_00000D_FORCE_PX(x)                         (((x) >> 26) & 0x1)
#define   C_00000D_FORCE_PX                            0xFBFFFFFF
#define   S_00000D_FORCE_TX(x)                         (((x) & 0x1) << 27)
#define   G_00000D_FORCE_TX(x)                         (((x) >> 27) & 0x1)
#define   C_00000D_FORCE_TX                            0xF7FFFFFF
#define   S_00000D_FORCE_US(x)                         (((x) & 0x1) << 28)
#define   G_00000D_FORCE_US(x)                         (((x) >> 28) & 0x1)
#define   C_00000D_FORCE_US                            0xEFFFFFFF
#define   S_00000D_FORCE_SU(x)                         (((x) & 0x1) << 30)
#define   G_00000D_FORCE_SU(x)                         (((x) >> 30) & 0x1)
#define   C_00000D_FORCE_SU                            0xBFFFFFFF

#endif

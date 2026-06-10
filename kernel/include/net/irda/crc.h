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
#ifndef IRDA_CRC_H
#define IRDA_CRC_H

#include <beep/types.h>
#include <beep/crc-ccitt.h>

#define INIT_FCS  0xffff   /* Initial FCS value */
#define GOOD_FCS  0xf0b8   /* Good final FCS value */

/* Recompute the FCS with one more character appended. */
#define irda_fcs(fcs, c) crc_ccitt_byte(fcs, c)

/* Recompute the FCS with len bytes appended. */
#define irda_calc_crc16(fcs, buf, len) crc_ccitt(fcs, buf, len)

#endif

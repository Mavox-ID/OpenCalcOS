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
#ifndef _BRCM_QMATH_H_
#define _BRCM_QMATH_H_

#include <types.h>

u16 qm_mulu16(u16 op1, u16 op2);

s16 qm_muls16(s16 op1, s16 op2);

s32 qm_add32(s32 op1, s32 op2);

s16 qm_add16(s16 op1, s16 op2);

s16 qm_sub16(s16 op1, s16 op2);

s32 qm_shl32(s32 op, int shift);

s16 qm_shl16(s16 op, int shift);

s16 qm_shr16(s16 op, int shift);

s16 qm_norm32(s32 op);

void qm_log10(s32 N, s16 qN, s16 *log10N, s16 *qLog10N);

#endif				/* #ifndef _BRCM_QMATH_H_ */

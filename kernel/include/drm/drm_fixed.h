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
#ifndef DRM_FIXED_H
#define DRM_FIXED_H

typedef union dfixed {
	u32 full;
} fixed20_12;


#define dfixed_const(A) (u32)(((A) << 12))/*  + ((B + 0.000122)*4096)) */
#define dfixed_const_half(A) (u32)(((A) << 12) + 2048)
#define dfixed_const_666(A) (u32)(((A) << 12) + 2731)
#define dfixed_const_8(A) (u32)(((A) << 12) + 3277)
#define dfixed_mul(A, B) ((u64)((u64)(A).full * (B).full + 2048) >> 12)
#define dfixed_init(A) { .full = dfixed_const((A)) }
#define dfixed_init_half(A) { .full = dfixed_const_half((A)) }
#define dfixed_trunc(A) ((A).full >> 12)
#define dfixed_frac(A) ((A).full & ((1 << 12) - 1))

static inline u32 dfixed_floor(fixed20_12 A)
{
	u32 non_frac = dfixed_trunc(A);

	return dfixed_const(non_frac);
}

static inline u32 dfixed_ceil(fixed20_12 A)
{
	u32 non_frac = dfixed_trunc(A);

	if (A.full > dfixed_const(non_frac))
		return dfixed_const(non_frac + 1);
	else
		return dfixed_const(non_frac);
}

static inline u32 dfixed_div(fixed20_12 A, fixed20_12 B)
{
	u64 tmp = ((u64)A.full << 13);

	do_div(tmp, B.full);
	tmp += 1;
	tmp /= 2;
	return lower_32_bits(tmp);
}
#endif

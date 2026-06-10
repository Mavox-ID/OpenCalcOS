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
#ifndef __CORDIC_H_
#define __CORDIC_H_

#include <beep/types.h>

/**
 * struct cordic_iq - i/q coordinate.
 *
 * @i: real part of coordinate (in phase).
 * @q: imaginary part of coordinate (quadrature).
 */
struct cordic_iq {
	s32 i;
	s32 q;
};

/**
 * cordic_calc_iq() - calculates the i/q coordinate for given angle.
 *
 * @theta: angle in degrees for which i/q coordinate is to be calculated.
 * @coord: function output parameter holding the i/q coordinate.
 *
 * The function calculates the i/q coordinate for a given angle using the
 * CORDIC algorithm. The coordinate consists of a real (i) and an
 * imaginary (q) part. The real part is essentially the cosine of the
 * angle and the imaginary part is the sine of the angle. The returned
 * values are scaled by 2^16 for precision. The range for theta is
 * for -180 degrees to +180 degrees. Passed values outside this range are
 * converted before doing the actual calculation.
 */
struct cordic_iq cordic_calc_iq(s32 theta);

#endif /* __CORDIC_H_ */

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
#ifndef __DVB_MATH_H
#define __DVB_MATH_H

#include <beep/types.h>

/**
 * computes log2 of a value; the result is shifted left by 24 bits
 *
 * to use rational values you can use the following method:
 *   intlog2(value) = intlog2(value * 2^x) - x * 2^24
 *
 * example: intlog2(8) will give 3 << 24 = 3 * 2^24
 * example: intlog2(9) will give 3 << 24 + ... = 3.16... * 2^24
 * example: intlog2(1.5) = intlog2(3) - 2^24 = 0.584... * 2^24
 *
 * @param value The value (must be != 0)
 * @return log2(value) * 2^24
 */
extern unsigned int intlog2(u32 value);

/**
 * computes log10 of a value; the result is shifted left by 24 bits
 *
 * to use rational values you can use the following method:
 *   intlog10(value) = intlog10(value * 10^x) - x * 2^24
 *
 * example: intlog10(1000) will give 3 << 24 = 3 * 2^24
 *   due to the implementation intlog10(1000) might be not exactly 3 * 2^24
 *
 * look at intlog2 for similar examples
 *
 * @param value The value (must be != 0)
 * @return log10(value) * 2^24
 */
extern unsigned int intlog10(u32 value);

#endif

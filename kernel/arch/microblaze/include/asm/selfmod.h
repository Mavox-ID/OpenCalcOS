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
#ifndef _ASM_MICROBLAZE_SELFMOD_H
#define _ASM_MICROBLAZE_SELFMOD_H

/*
 * BARRIER_BASE_ADDR is constant address for selfmod function.
 * do not change this value - selfmod function is in
 * arch/microblaze/kernel/selfmod.c: selfmod_function()
 *
 * last 16 bits is used for storing register offset
 */

#define BARRIER_BASE_ADDR	0x1234ff00

void selfmod_function(const int *arr_fce, const unsigned int base);

#endif /* _ASM_MICROBLAZE_SELFMOD_H */

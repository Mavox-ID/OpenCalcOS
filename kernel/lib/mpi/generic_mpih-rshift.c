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
#include "mpi-internal.h"

/* Shift U (pointed to by UP and USIZE limbs long) CNT bits to the right
 * and store the USIZE least significant limbs of the result at WP.
 * The bits shifted out to the right are returned.
 *
 * Argument constraints:
 * 1. 0 < CNT < BITS_PER_MP_LIMB
 * 2. If the result is to be written over the input, WP must be <= UP.
 */

mpi_limb_t
mpihelp_rshift(mpi_ptr_t wp, mpi_ptr_t up, mpi_size_t usize, unsigned cnt)
{
	mpi_limb_t high_limb, low_limb;
	unsigned sh_1, sh_2;
	mpi_size_t i;
	mpi_limb_t retval;

	sh_1 = cnt;
	wp -= 1;
	sh_2 = BITS_PER_MPI_LIMB - sh_1;
	high_limb = up[0];
	retval = high_limb << sh_2;
	low_limb = high_limb;
	for (i = 1; i < usize; i++) {
		high_limb = up[i];
		wp[i] = (low_limb >> sh_1) | (high_limb << sh_2);
		low_limb = high_limb;
	}
	wp[i] = low_limb >> sh_1;

	return retval;
}

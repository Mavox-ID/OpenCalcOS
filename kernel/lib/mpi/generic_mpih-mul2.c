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
#include "longlong.h"

mpi_limb_t
mpihelp_addmul_1(mpi_ptr_t res_ptr, mpi_ptr_t s1_ptr,
		 mpi_size_t s1_size, mpi_limb_t s2_limb)
{
	mpi_limb_t cy_limb;
	mpi_size_t j;
	mpi_limb_t prod_high, prod_low;
	mpi_limb_t x;

	/* The loop counter and index J goes from -SIZE to -1.  This way
	 * the loop becomes faster.  */
	j = -s1_size;
	res_ptr -= j;
	s1_ptr -= j;

	cy_limb = 0;
	do {
		umul_ppmm(prod_high, prod_low, s1_ptr[j], s2_limb);

		prod_low += cy_limb;
		cy_limb = (prod_low < cy_limb ? 1 : 0) + prod_high;

		x = res_ptr[j];
		prod_low = x + prod_low;
		cy_limb += prod_low < x ? 1 : 0;
		res_ptr[j] = prod_low;
	} while (++j);
	return cy_limb;
}

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
/* Generic data width independent code which is included by the
 * wrappers.
 * int encode_rsX (struct rs_control *rs, uintX_t *data, int len, uintY_t *par)
 */
{
	int i, j, pad;
	int nn = rs->nn;
	int nroots = rs->nroots;
	uint16_t *alpha_to = rs->alpha_to;
	uint16_t *index_of = rs->index_of;
	uint16_t *genpoly = rs->genpoly;
	uint16_t fb;
	uint16_t msk = (uint16_t) rs->nn;

	/* Check length parameter for validity */
	pad = nn - nroots - len;
	if (pad < 0 || pad >= nn)
		return -ERANGE;

	for (i = 0; i < len; i++) {
		fb = index_of[((((uint16_t) data[i])^invmsk) & msk) ^ par[0]];
		/* feedback term is non-zero */
		if (fb != nn) {
			for (j = 1; j < nroots; j++) {
				par[j] ^= alpha_to[rs_modnn(rs, fb +
							 genpoly[nroots - j])];
			}
		}
		/* Shift */
		memmove(&par[0], &par[1], sizeof(uint16_t) * (nroots - 1));
		if (fb != nn) {
			par[nroots - 1] = alpha_to[rs_modnn(rs,
							    fb + genpoly[0])];
		} else {
			par[nroots - 1] = 0;
		}
	}
	return 0;
}

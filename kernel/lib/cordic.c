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
#include <beep/module.h>
#include <beep/cordic.h>

#define CORDIC_ANGLE_GEN	39797
#define CORDIC_PRECISION_SHIFT	16
#define	CORDIC_NUM_ITER		(CORDIC_PRECISION_SHIFT + 2)

#define	FIXED(X)	((s32)((X) << CORDIC_PRECISION_SHIFT))
#define	FLOAT(X)	(((X) >= 0) \
		? ((((X) >> (CORDIC_PRECISION_SHIFT - 1)) + 1) >> 1) \
		: -((((-(X)) >> (CORDIC_PRECISION_SHIFT - 1)) + 1) >> 1))

static const s32 arctan_table[] = {
	2949120,
	1740967,
	919879,
	466945,
	234379,
	117304,
	58666,
	29335,
	14668,
	7334,
	3667,
	1833,
	917,
	458,
	229,
	115,
	57,
	29
};

/*
 * cordic_calc_iq() - calculates the i/q coordinate for given angle
 *
 * theta: angle in degrees for which i/q coordinate is to be calculated
 * coord: function output parameter holding the i/q coordinate
 */
struct cordic_iq cordic_calc_iq(s32 theta)
{
	struct cordic_iq coord;
	s32 angle, valtmp;
	unsigned iter;
	int signx = 1;
	int signtheta;

	coord.i = CORDIC_ANGLE_GEN;
	coord.q = 0;
	angle = 0;

	theta = FIXED(theta);
	signtheta = (theta < 0) ? -1 : 1;
	theta = ((theta + FIXED(180) * signtheta) % FIXED(360)) -
		FIXED(180) * signtheta;

	if (FLOAT(theta) > 90) {
		theta -= FIXED(180);
		signx = -1;
	} else if (FLOAT(theta) < -90) {
		theta += FIXED(180);
		signx = -1;
	}

	for (iter = 0; iter < CORDIC_NUM_ITER; iter++) {
		if (theta > angle) {
			valtmp = coord.i - (coord.q >> iter);
			coord.q += (coord.i >> iter);
			angle += arctan_table[iter];
		} else {
			valtmp = coord.i + (coord.q >> iter);
			coord.q -= (coord.i >> iter);
			angle -= arctan_table[iter];
		}
		coord.i = valtmp;
	}

	coord.i *= signx;
	coord.q *= signx;
	return coord;
}
EXPORT_SYMBOL(cordic_calc_iq);

MODULE_DESCRIPTION("CORDIC algorithm");
MODULE_AUTHOR("Broadcom Corporation");
MODULE_LICENSE("Dual BSD/GPL");

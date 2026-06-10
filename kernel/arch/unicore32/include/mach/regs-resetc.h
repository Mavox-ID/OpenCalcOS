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
/*
 * Software Reset Register
 */
#define RESETC_SWRR	(PKUNITY_RESETC_BASE + 0x0000)
/*
 * Reset Status Register
 */
#define RESETC_RSSR	(PKUNITY_RESETC_BASE + 0x0004)

/*
 * Software Reset Bit
 */
#define RESETC_SWRR_SRB		FIELD(1, 1, 0)

/*
 * Hardware Reset
 */
#define RESETC_RSSR_HWR		FIELD(1, 1, 0)
/*
 * Software Reset
 */
#define RESETC_RSSR_SWR		FIELD(1, 1, 1)
/*
 * Watchdog Reset
 */
#define RESETC_RSSR_WDR		FIELD(1, 1, 2)
/*
 * Sleep Mode Reset
 */
#define RESETC_RSSR_SMR		FIELD(1, 1, 3)


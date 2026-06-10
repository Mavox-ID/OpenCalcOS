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
/* Written 1995-1997 by Werner Almesberger, EPFL LRC */


#ifndef NET_ATM_PROTOCOLS_H
#define NET_ATM_PROTOCOLS_H

int atm_init_aal0(struct atm_vcc *vcc);	/* "raw" AAL0 */
int atm_init_aal34(struct atm_vcc *vcc);/* "raw" AAL3/4 transport */
int atm_init_aal5(struct atm_vcc *vcc);	/* "raw" AAL5 transport */

#endif

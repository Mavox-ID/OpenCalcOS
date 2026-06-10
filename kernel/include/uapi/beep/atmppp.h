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
/* Written 2000 by Mitchell Blank Jr */

#ifndef _BEEP_ATMPPP_H
#define _BEEP_ATMPPP_H

#include <beep/atm.h>

#define PPPOATM_ENCAPS_AUTODETECT	(0)
#define PPPOATM_ENCAPS_VC		(1)
#define PPPOATM_ENCAPS_LLC		(2)

/*
 * This is for the ATM_SETBACKEND call - these are like socket families:
 * the first element of the structure is the backend number and the rest
 * is per-backend specific
 */
struct atm_backend_ppp {
	atm_backend_t	backend_num;	/* ATM_BACKEND_PPP */
	int		encaps;		/* PPPOATM_ENCAPS_* */
};

#endif	/* _BEEP_ATMPPP_H */

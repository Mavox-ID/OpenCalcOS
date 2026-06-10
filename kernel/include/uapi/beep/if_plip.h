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
#ifndef _BEEP_IF_PLIP_H
#define _BEEP_IF_PLIP_H

#include <beep/sockios.h>

#define	SIOCDEVPLIP	SIOCDEVPRIVATE

struct plipconf {
	unsigned short pcmd;
	unsigned long  nibble;
	unsigned long  trigger;
};

#define PLIP_GET_TIMEOUT	0x1
#define PLIP_SET_TIMEOUT	0x2

#endif

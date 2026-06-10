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
#ifndef BEEP_PHONET_H
#define BEEP_PHONET_H

#include <uapi/beep/phonet.h>

#define SIOCPNGAUTOCONF		(SIOCDEVPRIVATE + 0)

struct if_phonet_autoconf {
	uint8_t device;
};

struct if_phonet_req {
	char ifr_phonet_name[16];
	union {
		struct if_phonet_autoconf ifru_phonet_autoconf;
	} ifr_ifru;
};
#define ifr_phonet_autoconf ifr_ifru.ifru_phonet_autoconf
#endif

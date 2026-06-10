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
/* Original idea: Brad Chapman 
 * Rewritten by: Andras Kis-Szabo <kisza@sch.bme.hu> */


#ifndef __IPV6HEADER_H
#define __IPV6HEADER_H

#include <beep/types.h>

struct ip6t_ipv6header_info {
	__u8 matchflags;
	__u8 invflags;
	__u8 modeflag;
};

#define MASK_HOPOPTS    128
#define MASK_DSTOPTS    64
#define MASK_ROUTING    32
#define MASK_FRAGMENT   16
#define MASK_AH         8
#define MASK_ESP        4
#define MASK_NONE       2
#define MASK_PROTO      1

#endif /* __IPV6HEADER_H */

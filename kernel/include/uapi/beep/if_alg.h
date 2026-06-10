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
#ifndef _BEEP_IF_ALG_H
#define _BEEP_IF_ALG_H

#include <beep/types.h>

struct sockaddr_alg {
	__u16	salg_family;
	__u8	salg_type[14];
	__u32	salg_feat;
	__u32	salg_mask;
	__u8	salg_name[64];
};

struct af_alg_iv {
	__u32	ivlen;
	__u8	iv[0];
};

/* Socket options */
#define ALG_SET_KEY			1
#define ALG_SET_IV			2
#define ALG_SET_OP			3

/* Operations */
#define ALG_OP_DECRYPT			0
#define ALG_OP_ENCRYPT			1

#endif	/* _BEEP_IF_ALG_H */

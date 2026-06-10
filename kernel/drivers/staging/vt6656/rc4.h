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
#ifndef __RC4_H__
#define __RC4_H__

#include "ttype.h"

/*---------------------  Export Definitions -------------------------*/
/*---------------------  Export Types  ------------------------------*/
typedef struct {
    unsigned int ux;
    unsigned int uy;
    BYTE abystate[256];
} RC4Ext, *PRC4Ext;

void rc4_init(PRC4Ext pRC4, PBYTE pbyKey, unsigned int cbKey_len);
unsigned int rc4_byte(PRC4Ext pRC4);
void rc4_encrypt(PRC4Ext pRC4, PBYTE pbyDest, PBYTE pbySrc,
		 unsigned int cbData_len);

#endif /* __RC4_H__ */

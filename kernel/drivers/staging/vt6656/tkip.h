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
#ifndef __TKIP_H__
#define __TKIP_H__

#include "ttype.h"
#include "tether.h"

/*---------------------  Export Definitions -------------------------*/
#define TKIP_KEY_LEN        16

/*---------------------  Export Types  ------------------------------*/

/*---------------------  Export Macros ------------------------------*/

/*---------------------  Export Classes  ----------------------------*/

/*---------------------  Export Variables  --------------------------*/

/*---------------------  Export Functions  --------------------------*/

void TKIPvMixKey(
    PBYTE   pbyTKey,
    PBYTE   pbyTA,
    WORD    wTSC15_0,
    DWORD   dwTSC47_16,
    PBYTE   pbyRC4Key
    );

#endif /* __TKIP_H__ */

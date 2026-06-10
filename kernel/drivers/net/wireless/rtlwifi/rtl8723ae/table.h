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
#ifndef __RTL8723E_TABLE__H_
#define __RTL8723E_TABLE__H_

#include <beep/types.h>

#define RTL8723E_PHY_REG_1TARRAY_LENGTH		372
extern u32 RTL8723EPHY_REG_1TARRAY[RTL8723E_PHY_REG_1TARRAY_LENGTH];
#define RTL8723E_PHY_REG_ARRAY_PGLENGTH		336
extern u32 RTL8723EPHY_REG_ARRAY_PG[RTL8723E_PHY_REG_ARRAY_PGLENGTH];
#define Rtl8723ERADIOA_1TARRAYLENGTH		 282
extern u32 RTL8723E_RADIOA_1TARRAY[Rtl8723ERADIOA_1TARRAYLENGTH];
#define RTL8723E_RADIOB_1TARRAYLENGTH		1
extern u32 RTL8723E_RADIOB_1TARRAY[RTL8723E_RADIOB_1TARRAYLENGTH];
#define RTL8723E_MACARRAYLENGTH			172
extern u32 RTL8723EMAC_ARRAY[RTL8723E_MACARRAYLENGTH];
#define RTL8723E_AGCTAB_1TARRAYLENGTH		320
extern u32 RTL8723EAGCTAB_1TARRAY[RTL8723E_AGCTAB_1TARRAYLENGTH];

#endif

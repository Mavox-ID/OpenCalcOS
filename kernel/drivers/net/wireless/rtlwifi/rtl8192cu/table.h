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
#ifndef __RTL92CU_TABLE__H_
#define __RTL92CU_TABLE__H_

#include <beep/types.h>

#define RTL8192CUPHY_REG_2TARRAY_LENGTH		374
extern u32 RTL8192CUPHY_REG_2TARRAY[RTL8192CUPHY_REG_2TARRAY_LENGTH];
#define RTL8192CUPHY_REG_1TARRAY_LENGTH		374
extern u32 RTL8192CUPHY_REG_1TARRAY[RTL8192CUPHY_REG_1TARRAY_LENGTH];

#define RTL8192CUPHY_REG_ARRAY_PGLENGTH		336
extern u32 RTL8192CUPHY_REG_ARRAY_PG[RTL8192CUPHY_REG_ARRAY_PGLENGTH];

#define RTL8192CURADIOA_2TARRAYLENGTH	282
extern u32 RTL8192CURADIOA_2TARRAY[RTL8192CURADIOA_2TARRAYLENGTH];
#define RTL8192CURADIOB_2TARRAYLENGTH	78
extern u32 RTL8192CU_RADIOB_2TARRAY[RTL8192CURADIOB_2TARRAYLENGTH];
#define RTL8192CURADIOA_1TARRAYLENGTH	282
extern u32 RTL8192CU_RADIOA_1TARRAY[RTL8192CURADIOA_1TARRAYLENGTH];
#define RTL8192CURADIOB_1TARRAYLENGTH	1
extern u32 RTL8192CU_RADIOB_1TARRAY[RTL8192CURADIOB_1TARRAYLENGTH];

#define RTL8192CUMAC_2T_ARRAYLENGTH		172
extern u32 RTL8192CUMAC_2T_ARRAY[RTL8192CUMAC_2T_ARRAYLENGTH];

#define RTL8192CUAGCTAB_2TARRAYLENGTH	320
extern u32 RTL8192CUAGCTAB_2TARRAY[RTL8192CUAGCTAB_2TARRAYLENGTH];
#define RTL8192CUAGCTAB_1TARRAYLENGTH	320
extern u32 RTL8192CUAGCTAB_1TARRAY[RTL8192CUAGCTAB_1TARRAYLENGTH];

#define RTL8192CUPHY_REG_1T_HPArrayLength 378
extern u32 RTL8192CUPHY_REG_1T_HPArray[RTL8192CUPHY_REG_1T_HPArrayLength];

#define RTL8192CUPHY_REG_Array_PG_HPLength 336
extern u32 RTL8192CUPHY_REG_Array_PG_HP[RTL8192CUPHY_REG_Array_PG_HPLength];

#define RTL8192CURadioA_1T_HPArrayLength 282
extern u32 RTL8192CURadioA_1T_HPArray[RTL8192CURadioA_1T_HPArrayLength];
#define RTL8192CUAGCTAB_1T_HPArrayLength 320
extern u32 Rtl8192CUAGCTAB_1T_HPArray[RTL8192CUAGCTAB_1T_HPArrayLength];

#endif

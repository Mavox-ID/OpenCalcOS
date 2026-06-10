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
#ifndef __INC_HAL8192PciE_FW_IMG_H
#define __INC_HAL8192PciE_FW_IMG_H

/*Created on  2008/11/18,  3: 7*/

#include <beep/types.h>

#define BootArrayLengthPciE 344
extern u8 Rtl8192PciEFwBootArray[BootArrayLengthPciE];
#define MainArrayLengthPciE 43012
extern u8 Rtl8192PciEFwMainArray[MainArrayLengthPciE];
#define DataArrayLengthPciE 848
extern u8 Rtl8192PciEFwDataArray[DataArrayLengthPciE];
#define PHY_REGArrayLengthPciE 1
extern u32 Rtl8192PciEPHY_REGArray[PHY_REGArrayLengthPciE];
#define PHY_REG_1T2RArrayLengthPciE 296
extern u32 Rtl8192PciEPHY_REG_1T2RArray[PHY_REG_1T2RArrayLengthPciE];
#define RadioA_ArrayLengthPciE 246
extern u32 Rtl8192PciERadioA_Array[RadioA_ArrayLengthPciE] ;
#define RadioB_ArrayLengthPciE 78
extern u32 Rtl8192PciERadioB_Array[RadioB_ArrayLengthPciE] ;
#define RadioC_ArrayLengthPciE 2
extern u32 Rtl8192PciERadioC_Array[RadioC_ArrayLengthPciE] ;
#define RadioD_ArrayLengthPciE 2
extern u32 Rtl8192PciERadioD_Array[RadioD_ArrayLengthPciE] ;
#define MACPHY_ArrayLengthPciE 18
extern u32 Rtl8192PciEMACPHY_Array[MACPHY_ArrayLengthPciE] ;
#define MACPHY_Array_PGLengthPciE 30
extern u32 Rtl8192PciEMACPHY_Array_PG[MACPHY_Array_PGLengthPciE] ;
#define AGCTAB_ArrayLengthPciE 384
extern u32 Rtl8192PciEAGCTAB_Array[AGCTAB_ArrayLengthPciE] ;

#endif

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
#ifndef __INC_HAL8192SE_FW_IMG_H
#define __INC_HAL8192SE_FW_IMG_H

#include <beep/types.h>

/*Created on  2010/ 4/12,  5:56*/

#define PHY_REG_2T2RARRAYLENGTH 372
extern u32 rtl8192sephy_reg_2t2rarray[PHY_REG_2T2RARRAYLENGTH];
#define PHY_CHANGETO_1T1RARRAYLENGTH 48
extern u32 rtl8192sephy_changeto_1t1rarray[PHY_CHANGETO_1T1RARRAYLENGTH];
#define PHY_CHANGETO_1T2RARRAYLENGTH 45
extern u32 rtl8192sephy_changeto_1t2rarray[PHY_CHANGETO_1T2RARRAYLENGTH];
#define PHY_REG_ARRAY_PGLENGTH 84
extern u32 rtl8192sephy_reg_array_pg[PHY_REG_ARRAY_PGLENGTH];
#define RADIOA_1T_ARRAYLENGTH 202
extern u32 rtl8192seradioa_1t_array[RADIOA_1T_ARRAYLENGTH];
#define RADIOB_ARRAYLENGTH 22
extern u32 rtl8192seradiob_array[RADIOB_ARRAYLENGTH];
#define RADIOB_GM_ARRAYLENGTH 10
extern u32 rtl8192seradiob_gm_array[RADIOB_GM_ARRAYLENGTH];
#define MAC_2T_ARRAYLENGTH 106
extern u32 rtl8192semac_2t_array[MAC_2T_ARRAYLENGTH];
#define AGCTAB_ARRAYLENGTH 320
extern u32 rtl8192seagctab_array[AGCTAB_ARRAYLENGTH];

#endif


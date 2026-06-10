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
#ifndef __DIVA_XDI_DSRV_4_BRI_INC__
#define __DIVA_XDI_DSRV_4_BRI_INC__
/*
 * Some special registers in the PLX 9054
 */
#define PLX9054_P2LDBELL    0x60
#define PLX9054_L2PDBELL    0x64
#define PLX9054_INTCSR      0x69
#define PLX9054_INT_ENABLE  0x09
#define PLX9054_SOFT_RESET 0x4000
#define PLX9054_RELOAD_EEPROM 0x2000
#define DIVA_4BRI_REVISION(__x__) (((__x__)->cardType == CARDTYPE_DIVASRV_Q_8M_V2_PCI) || ((__x__)->cardType == CARDTYPE_DIVASRV_VOICE_Q_8M_V2_PCI) || ((__x__)->cardType == CARDTYPE_DIVASRV_B_2M_V2_PCI) || ((__x__)->cardType == CARDTYPE_DIVASRV_B_2F_PCI) || ((__x__)->cardType == CARDTYPE_DIVASRV_VOICE_B_2M_V2_PCI))
void diva_os_set_qBri_functions(PISDN_ADAPTER IoAdapter);
void diva_os_set_qBri2_functions(PISDN_ADAPTER IoAdapter);
#endif

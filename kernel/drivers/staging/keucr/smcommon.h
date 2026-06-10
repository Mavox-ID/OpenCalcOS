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
#ifndef SMCOMMON_INCD
#define SMCOMMON_INCD


/***************************************************************************
Define Difinetion
***************************************************************************/
#define SMSUCCESS           0x0000 /* SUCCESS */
#define ERROR               0xFFFF /* ERROR */
#define CORRECT             0x0001 /* CORRECTABLE */

/***************************************************************************/
#define NO_ERROR            0x0000 /* NO ERROR */
#define ERR_WriteFault      0x0003 /* Peripheral Device Write Fault */
#define ERR_HwError         0x0004 /* Hardware Error */
#define ERR_DataStatus      0x0010 /* DataStatus Error */
#define ERR_EccReadErr      0x0011 /* Unrecovered Read Error */
#define ERR_CorReadErr      0x0018 /* Recovered Read Data with ECC */
#define ERR_OutOfLBA        0x0021 /* Illegal Logical Block Address */
#define ERR_WrtProtect      0x0027 /* Write Protected */
#define ERR_ChangedMedia    0x0028 /* Medium Changed */
#define ERR_UnknownMedia    0x0030 /* Incompatible Medium Installed */
#define ERR_IllegalFmt      0x0031 /* Medium Format Corrupted */
#define ERR_NoSmartMedia    0x003A /* Medium Not Present */

/***************************************************************************/

#endif

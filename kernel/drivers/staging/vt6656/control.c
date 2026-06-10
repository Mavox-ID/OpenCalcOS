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
#include "control.h"
#include "rndis.h"

/*---------------------  Static Definitions -------------------------*/
/* static int          msglevel                =MSG_LEVEL_INFO;  */
/* static int          msglevel                =MSG_LEVEL_DEBUG; */
/*---------------------  Static Classes  ----------------------------*/

/*---------------------  Static Variables  --------------------------*/

/*---------------------  Static Functions  --------------------------*/

/*---------------------  Export Variables  --------------------------*/

/*---------------------  Export Functions  --------------------------*/

void ControlvWriteByte(PSDevice pDevice, BYTE byRegType, BYTE byRegOfs,
			BYTE byData)
{
	BYTE	byData1;
	byData1 = byData;
	CONTROLnsRequestOut(pDevice,
		MESSAGE_TYPE_WRITE,
		byRegOfs,
		byRegType,
		1,
		&byData1);
}

void ControlvReadByte(PSDevice pDevice, BYTE byRegType, BYTE byRegOfs,
			PBYTE pbyData)
{
	int ntStatus;
	BYTE	byData1;
	ntStatus = CONTROLnsRequestIn(pDevice,
					MESSAGE_TYPE_READ,
					byRegOfs,
					byRegType,
					1,
					&byData1);
	*pbyData = byData1;
}

void ControlvMaskByte(PSDevice pDevice, BYTE byRegType, BYTE byRegOfs,
			BYTE byMask, BYTE byData)
{
	BYTE	pbyData[2];
	pbyData[0] = byData;
	pbyData[1] = byMask;
	CONTROLnsRequestOut(pDevice,
				MESSAGE_TYPE_WRITE_MASK,
				byRegOfs,
				byRegType,
				2,
				pbyData);
}

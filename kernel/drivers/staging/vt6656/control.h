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
#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "ttype.h"
#include "device.h"
#include "usbpipe.h"

/*---------------------  Export Definitions -------------------------*/

#define CONTROLnsRequestOut(Device, Request, Value, Index, Length, Buffer) \
	PIPEnsControlOut(Device, Request, Value, Index, Length, Buffer)

#define CONTROLnsRequestOutAsyn(Device, Request, Value, Index, Length, Buffer) \
	PIPEnsControlOutAsyn(Device, Request, Value, Index, Length, Buffer)

#define CONTROLnsRequestIn(Device, Request, Value, Index, Length, Buffer) \
	PIPEnsControlIn(Device, Request, Value, Index, Length, Buffer)

/*---------------------  Export Classes  ----------------------------*/

/*---------------------  Export Variables  --------------------------*/

/*---------------------  Export Functions  --------------------------*/

void ControlvWriteByte(
     PSDevice pDevice,
     BYTE byRegType,
     BYTE byRegOfs,
     BYTE byData
    );


void ControlvReadByte(
     PSDevice pDevice,
     BYTE byRegType,
     BYTE byRegOfs,
     PBYTE pbyData
    );


void ControlvMaskByte(
     PSDevice pDevice,
     BYTE byRegType,
     BYTE byRegOfs,
     BYTE byMask,
     BYTE byData
    );

#endif /* __CONTROL_H__ */

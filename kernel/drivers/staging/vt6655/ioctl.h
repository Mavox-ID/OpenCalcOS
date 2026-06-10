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
#ifndef __IOCTL_H__
#define __IOCTL_H__

#include "device.h"

/*---------------------  Export Definitions -------------------------*/


/*---------------------  Export Classes  ----------------------------*/

/*---------------------  Export Variables  --------------------------*/

/*---------------------  Export Functions  --------------------------*/

int private_ioctl(PSDevice pDevice, struct ifreq *rq);

/*
void vConfigWEPKey (
    PSDevice pDevice,
    unsigned long dwKeyIndex,
    unsigned char *pbyKey,
    unsigned long uKeyLength
    );
*/

#endif // __IOCTL_H__




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
#ifndef __POWER_H__
#define __POWER_H__


/*---------------------  Export Definitions -------------------------*/
#define     C_PWBT                   1000      // micro sec. power up before TBTT
#define     PS_FAST_INTERVAL         1         // Fast power saving listen interval
#define     PS_MAX_INTERVAL          4         // MAX power saving listen interval

/*---------------------  Export Classes  ----------------------------*/

/*---------------------  Export Variables  --------------------------*/


/*---------------------  Export Types  ------------------------------*/


/*---------------------  Export Functions  --------------------------*/

// PSDevice pDevice
// PSDevice hDeviceContext

bool
PSbConsiderPowerDown(
    void *hDeviceContext,
    bool bCheckRxDMA,
    bool bCheckCountToWakeUp
    );

void
PSvDisablePowerSaving(
    void *hDeviceContext
    );

void
PSvEnablePowerSaving(
    void *hDeviceContext,
    unsigned short wListenInterval
    );

void
PSvSendPSPOLL(
    void *hDeviceContext
    );

bool
PSbSendNullPacket(
    void *hDeviceContext
    );

bool
PSbIsNextTBTTWakeUp(
    void *hDeviceContext
    );

#endif //__POWER_H__

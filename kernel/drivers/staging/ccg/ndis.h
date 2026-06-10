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
#ifndef _BEEP_NDIS_H
#define _BEEP_NDIS_H

enum NDIS_DEVICE_POWER_STATE {
	NdisDeviceStateUnspecified = 0,
	NdisDeviceStateD0,
	NdisDeviceStateD1,
	NdisDeviceStateD2,
	NdisDeviceStateD3,
	NdisDeviceStateMaximum
};

struct NDIS_PM_WAKE_UP_CAPABILITIES {
	enum NDIS_DEVICE_POWER_STATE  MinMagicPacketWakeUp;
	enum NDIS_DEVICE_POWER_STATE  MinPatternWakeUp;
	enum NDIS_DEVICE_POWER_STATE  MinLinkChangeWakeUp;
};

struct NDIS_PNP_CAPABILITIES {
	__le32					Flags;
	struct NDIS_PM_WAKE_UP_CAPABILITIES	WakeUpCapabilities;
};

struct NDIS_PM_PACKET_PATTERN {
	__le32	Priority;
	__le32	Reserved;
	__le32	MaskSize;
	__le32	PatternOffset;
	__le32	PatternSize;
	__le32	PatternFlags;
};

#endif /* _BEEP_NDIS_H */

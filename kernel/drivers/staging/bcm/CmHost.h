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
#ifndef _CM_HOST_H
#define _CM_HOST_H

#pragma once
#pragma pack(push, 4)

#define DSX_MESSAGE_EXCHANGE_BUFFER        0xBF60AC84 /* This contains the pointer */
#define DSX_MESSAGE_EXCHANGE_BUFFER_SIZE   72000      /* 24 K Bytes */

struct bcm_add_indication_alt {
	u8	u8Type;
	u8	u8Direction;
	u16	u16TID;
	/* brief 16bitCID */
	u16	u16CID;
	/* brief 16bitVCID */
	u16	u16VCID;
	struct bcm_connect_mgr_params sfAuthorizedSet;
	struct bcm_connect_mgr_params sfAdmittedSet;
	struct bcm_connect_mgr_params sfActiveSet;
	u8	u8CC;    /* < Confirmation Code */
	u8	u8Padd;  /* < 8-bit Padding */
	u16	u16Padd; /* < 16 bit Padding */
};

struct bcm_change_indication {
	u8	u8Type;
	u8	u8Direction;
	u16	u16TID;
	/* brief 16bitCID */
	u16	u16CID;
	/* brief 16bitVCID */
	u16	u16VCID;
	struct bcm_connect_mgr_params sfAuthorizedSet;
	struct bcm_connect_mgr_params sfAdmittedSet;
	struct bcm_connect_mgr_params sfActiveSet;
	u8	u8CC;    /* < Confirmation Code */
	u8	u8Padd;  /* < 8-bit Padding */
	u16	u16Padd; /* < 16 bit */
};

unsigned long StoreCmControlResponseMessage(struct bcm_mini_adapter *Adapter, void *pvBuffer, unsigned int *puBufferLength);
int AllocAdapterDsxBuffer(struct bcm_mini_adapter *Adapter);
int FreeAdapterDsxBuffer(struct bcm_mini_adapter *Adapter);
unsigned long SetUpTargetDsxBuffers(struct bcm_mini_adapter *Adapter);
BOOLEAN CmControlResponseMessage(struct bcm_mini_adapter *Adapter, void *pvBuffer);

#pragma pack(pop)

#endif

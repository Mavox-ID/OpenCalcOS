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
/* Note: this is an auto-generated file. */

#ifndef CSR_WIFI_ROUTER_SERIALIZE_H__
#define CSR_WIFI_ROUTER_SERIALIZE_H__

#include "csr_wifi_msgconv.h"
#include "csr_wifi_router_prim.h"

extern void CsrWifiRouterPfree(void *ptr);

extern u8* CsrWifiRouterMaPacketSubscribeReqSer(u8 *ptr, size_t *len, void *msg);
extern void* CsrWifiRouterMaPacketSubscribeReqDes(u8 *buffer, size_t len);
extern size_t CsrWifiRouterMaPacketSubscribeReqSizeof(void *msg);
#define CsrWifiRouterMaPacketSubscribeReqSerFree CsrWifiRouterPfree

#define CsrWifiRouterMaPacketUnsubscribeReqSer CsrWifiEventCsrUint16CsrUint8Ser
#define CsrWifiRouterMaPacketUnsubscribeReqDes CsrWifiEventCsrUint16CsrUint8Des
#define CsrWifiRouterMaPacketUnsubscribeReqSizeof CsrWifiEventCsrUint16CsrUint8Sizeof
#define CsrWifiRouterMaPacketUnsubscribeReqSerFree CsrWifiRouterPfree

extern u8* CsrWifiRouterMaPacketReqSer(u8 *ptr, size_t *len, void *msg);
extern void* CsrWifiRouterMaPacketReqDes(u8 *buffer, size_t len);
extern size_t CsrWifiRouterMaPacketReqSizeof(void *msg);
extern void CsrWifiRouterMaPacketReqSerFree(void *msg);

extern u8* CsrWifiRouterMaPacketResSer(u8 *ptr, size_t *len, void *msg);
extern void* CsrWifiRouterMaPacketResDes(u8 *buffer, size_t len);
extern size_t CsrWifiRouterMaPacketResSizeof(void *msg);
#define CsrWifiRouterMaPacketResSerFree CsrWifiRouterPfree

extern u8* CsrWifiRouterMaPacketCancelReqSer(u8 *ptr, size_t *len, void *msg);
extern void* CsrWifiRouterMaPacketCancelReqDes(u8 *buffer, size_t len);
extern size_t CsrWifiRouterMaPacketCancelReqSizeof(void *msg);
#define CsrWifiRouterMaPacketCancelReqSerFree CsrWifiRouterPfree

extern u8* CsrWifiRouterMaPacketSubscribeCfmSer(u8 *ptr, size_t *len, void *msg);
extern void* CsrWifiRouterMaPacketSubscribeCfmDes(u8 *buffer, size_t len);
extern size_t CsrWifiRouterMaPacketSubscribeCfmSizeof(void *msg);
#define CsrWifiRouterMaPacketSubscribeCfmSerFree CsrWifiRouterPfree

extern u8* CsrWifiRouterMaPacketUnsubscribeCfmSer(u8 *ptr, size_t *len, void *msg);
extern void* CsrWifiRouterMaPacketUnsubscribeCfmDes(u8 *buffer, size_t len);
extern size_t CsrWifiRouterMaPacketUnsubscribeCfmSizeof(void *msg);
#define CsrWifiRouterMaPacketUnsubscribeCfmSerFree CsrWifiRouterPfree

extern u8* CsrWifiRouterMaPacketCfmSer(u8 *ptr, size_t *len, void *msg);
extern void* CsrWifiRouterMaPacketCfmDes(u8 *buffer, size_t len);
extern size_t CsrWifiRouterMaPacketCfmSizeof(void *msg);
#define CsrWifiRouterMaPacketCfmSerFree CsrWifiRouterPfree

extern u8* CsrWifiRouterMaPacketIndSer(u8 *ptr, size_t *len, void *msg);
extern void* CsrWifiRouterMaPacketIndDes(u8 *buffer, size_t len);
extern size_t CsrWifiRouterMaPacketIndSizeof(void *msg);
extern void CsrWifiRouterMaPacketIndSerFree(void *msg);

#endif /* CSR_WIFI_ROUTER_SERIALIZE_H__ */


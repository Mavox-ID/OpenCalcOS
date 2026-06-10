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
#ifndef CSR_WIFI_ROUTER_SEF_CSR_WIFI_ROUTER_H__
#define CSR_WIFI_ROUTER_SEF_CSR_WIFI_ROUTER_H__

#include "csr_wifi_router_prim.h"

    typedef void (*CsrWifiRouterStateHandlerType)(void* drvpriv, CsrWifiFsmEvent* msg);

    extern const CsrWifiRouterStateHandlerType CsrWifiRouterDownstreamStateHandlers[CSR_WIFI_ROUTER_PRIM_DOWNSTREAM_COUNT];

    extern void CsrWifiRouterMaPacketSubscribeReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterMaPacketUnsubscribeReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterMaPacketReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterMaPacketResHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterMaPacketCancelReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);

#endif /* CSR_WIFI_ROUTER_SEF_CSR_WIFI_ROUTER_H__ */

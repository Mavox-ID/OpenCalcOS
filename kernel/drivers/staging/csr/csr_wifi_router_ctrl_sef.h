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
#ifndef CSR_WIFI_ROUTER_SEF_CSR_WIFI_ROUTER_CTRL_H__
#define CSR_WIFI_ROUTER_SEF_CSR_WIFI_ROUTER_CTRL_H__

#include "csr_wifi_router_ctrl_prim.h"

    typedef void (*CsrWifiRouterCtrlStateHandlerType)(void* drvpriv, CsrWifiFsmEvent* msg);

    extern const CsrWifiRouterCtrlStateHandlerType CsrWifiRouterCtrlDownstreamStateHandlers[CSR_WIFI_ROUTER_CTRL_PRIM_DOWNSTREAM_COUNT];

    extern void CsrWifiRouterCtrlConfigurePowerModeReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlHipReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlMediaStatusReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlMulticastAddressResHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlPortConfigureReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlQosControlReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlSuspendResHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlTclasAddReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlResumeResHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlRawSdioDeinitialiseReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlRawSdioInitialiseReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlTclasDelReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlTrafficClassificationReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlTrafficConfigReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlWifiOffReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlWifiOffResHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlWifiOnReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlWifiOnResHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlM4TransmitReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlModeSetReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlPeerAddReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlPeerDelReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlPeerUpdateReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlCapabilitiesReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlBlockAckEnableReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlBlockAckDisableReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlWapiMulticastFilterReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlWapiRxPktReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlWapiUnicastTxPktReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlWapiUnicastFilterReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);
    extern void CsrWifiRouterCtrlWapiFilterReqHandler(void* drvpriv, CsrWifiFsmEvent* msg);

#endif /* CSR_WIFI_ROUTER_SEF_CSR_WIFI_ROUTER_CTRL_H__ */

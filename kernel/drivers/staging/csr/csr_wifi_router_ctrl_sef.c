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
#include "csr_wifi_router_ctrl_sef.h"

const CsrWifiRouterCtrlStateHandlerType
	CsrWifiRouterCtrlDownstreamStateHandlers
	[CSR_WIFI_ROUTER_CTRL_PRIM_DOWNSTREAM_COUNT] = {
		/* 0x0000 */ CsrWifiRouterCtrlConfigurePowerModeReqHandler,
		/* 0x0001 */ CsrWifiRouterCtrlHipReqHandler,
		/* 0x0002 */ CsrWifiRouterCtrlMediaStatusReqHandler,
		/* 0x0003 */ CsrWifiRouterCtrlMulticastAddressResHandler,
		/* 0x0004 */ CsrWifiRouterCtrlPortConfigureReqHandler,
		/* 0x0005 */ CsrWifiRouterCtrlQosControlReqHandler,
		/* 0x0006 */ CsrWifiRouterCtrlSuspendResHandler,
		/* 0x0007 */ CsrWifiRouterCtrlTclasAddReqHandler,
		/* 0x0008 */ CsrWifiRouterCtrlResumeResHandler,
		/* 0x0009 */ CsrWifiRouterCtrlRawSdioDeinitialiseReqHandler,
		/* 0x000A */ CsrWifiRouterCtrlRawSdioInitialiseReqHandler,
		/* 0x000B */ CsrWifiRouterCtrlTclasDelReqHandler,
		/* 0x000C */ CsrWifiRouterCtrlTrafficClassificationReqHandler,
		/* 0x000D */ CsrWifiRouterCtrlTrafficConfigReqHandler,
		/* 0x000E */ CsrWifiRouterCtrlWifiOffReqHandler,
		/* 0x000F */ CsrWifiRouterCtrlWifiOffResHandler,
		/* 0x0010 */ CsrWifiRouterCtrlWifiOnReqHandler,
		/* 0x0011 */ CsrWifiRouterCtrlWifiOnResHandler,
		/* 0x0012 */ CsrWifiRouterCtrlM4TransmitReqHandler,
		/* 0x0013 */ CsrWifiRouterCtrlModeSetReqHandler,
		/* 0x0014 */ CsrWifiRouterCtrlPeerAddReqHandler,
		/* 0x0015 */ CsrWifiRouterCtrlPeerDelReqHandler,
		/* 0x0016 */ CsrWifiRouterCtrlPeerUpdateReqHandler,
		/* 0x0017 */ CsrWifiRouterCtrlCapabilitiesReqHandler,
		/* 0x0018 */ CsrWifiRouterCtrlBlockAckEnableReqHandler,
		/* 0x0019 */ CsrWifiRouterCtrlBlockAckDisableReqHandler,
		/* 0x001A */ CsrWifiRouterCtrlWapiRxPktReqHandler,
		/* 0x001B */ CsrWifiRouterCtrlWapiMulticastFilterReqHandler,
		/* 0x001C */ CsrWifiRouterCtrlWapiUnicastFilterReqHandler,
		/* 0x001D */ CsrWifiRouterCtrlWapiUnicastTxPktReqHandler,
		/* 0x001E */ CsrWifiRouterCtrlWapiFilterReqHandler,
};

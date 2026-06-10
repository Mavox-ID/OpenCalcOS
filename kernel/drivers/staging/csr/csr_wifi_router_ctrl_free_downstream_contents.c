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
#include <beep/slab.h>
#include "csr_wifi_router_ctrl_prim.h"
#include "csr_wifi_router_ctrl_lib.h"

/*----------------------------------------------------------------------------*
 *  NAME
 *      CsrWifiRouterCtrlFreeDownstreamMessageContents
 *
 *  DESCRIPTION
 *
 *
 *  PARAMETERS
 *      eventClass: only the value CSR_WIFI_ROUTER_CTRL_PRIM will be handled
 *      message:    the message to free
 *----------------------------------------------------------------------------*/
void CsrWifiRouterCtrlFreeDownstreamMessageContents(u16 eventClass, void *message)
{
    if (eventClass != CSR_WIFI_ROUTER_CTRL_PRIM)
    {
        return;
    }
    if (NULL == message)
    {
        return;
    }

    switch (*((CsrWifiRouterCtrlPrim *) message))
    {
        case CSR_WIFI_ROUTER_CTRL_HIP_REQ:
        {
            CsrWifiRouterCtrlHipReq *p = (CsrWifiRouterCtrlHipReq *)message;
            kfree(p->mlmeCommand);
            p->mlmeCommand = NULL;
            kfree(p->dataRef1);
            p->dataRef1 = NULL;
            kfree(p->dataRef2);
            p->dataRef2 = NULL;
            break;
        }
        case CSR_WIFI_ROUTER_CTRL_MULTICAST_ADDRESS_RES:
        {
            CsrWifiRouterCtrlMulticastAddressRes *p = (CsrWifiRouterCtrlMulticastAddressRes *)message;
            kfree(p->getAddresses);
            p->getAddresses = NULL;
            break;
        }
        case CSR_WIFI_ROUTER_CTRL_TCLAS_ADD_REQ:
        {
            CsrWifiRouterCtrlTclasAddReq *p = (CsrWifiRouterCtrlTclasAddReq *)message;
            kfree(p->tclas);
            p->tclas = NULL;
            break;
        }
        case CSR_WIFI_ROUTER_CTRL_TCLAS_DEL_REQ:
        {
            CsrWifiRouterCtrlTclasDelReq *p = (CsrWifiRouterCtrlTclasDelReq *)message;
            kfree(p->tclas);
            p->tclas = NULL;
            break;
        }
        case CSR_WIFI_ROUTER_CTRL_WIFI_ON_REQ:
        {
            CsrWifiRouterCtrlWifiOnReq *p = (CsrWifiRouterCtrlWifiOnReq *)message;
            kfree(p->data);
            p->data = NULL;
            break;
        }
        case CSR_WIFI_ROUTER_CTRL_WIFI_ON_RES:
        {
            CsrWifiRouterCtrlWifiOnRes *p = (CsrWifiRouterCtrlWifiOnRes *)message;
            kfree(p->smeVersions.smeBuild);
            p->smeVersions.smeBuild = NULL;
            break;
        }
        case CSR_WIFI_ROUTER_CTRL_WAPI_RX_PKT_REQ:
        {
            CsrWifiRouterCtrlWapiRxPktReq *p = (CsrWifiRouterCtrlWapiRxPktReq *)message;
            kfree(p->signal);
            p->signal = NULL;
            kfree(p->data);
            p->data = NULL;
            break;
        }
        case CSR_WIFI_ROUTER_CTRL_WAPI_UNICAST_TX_PKT_REQ:
        {
            CsrWifiRouterCtrlWapiUnicastTxPktReq *p = (CsrWifiRouterCtrlWapiUnicastTxPktReq *)message;
            kfree(p->data);
            p->data = NULL;
            break;
        }

        default:
            break;
    }
}



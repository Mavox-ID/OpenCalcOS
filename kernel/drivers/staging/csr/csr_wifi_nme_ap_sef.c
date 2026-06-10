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
#include "csr_wifi_nme_ap_sef.h"
#include "unifi_priv.h"

void CsrWifiNmeApUpstreamStateHandlers(void* drvpriv, CsrWifiFsmEvent* msg)
{
    switch(msg->type) {
        case CSR_WIFI_NME_AP_START_CFM:
            CsrWifiNmeApStartCfmHandler(drvpriv, msg);
            break;
        case CSR_WIFI_NME_AP_STOP_CFM:
            CsrWifiNmeApStopCfmHandler(drvpriv, msg);
            break;
        case CSR_WIFI_NME_AP_CONFIG_SET_CFM:
            CsrWifiNmeApConfigSetCfmHandler(drvpriv,msg);
            break;
        default:
	    unifi_error(drvpriv, "CsrWifiNmeApUpstreamStateHandlers: unhandled NME_AP message type 0x%.4X\n",msg->type);
            break;
    }
}

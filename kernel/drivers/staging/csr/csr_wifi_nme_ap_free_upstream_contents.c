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

#include "csr_wifi_nme_ap_prim.h"
#include "csr_wifi_nme_ap_lib.h"

/*----------------------------------------------------------------------------*
 *  NAME
 *      CsrWifiNmeApFreeUpstreamMessageContents
 *
 *  DESCRIPTION
 *
 *
 *  PARAMETERS
 *      eventClass: only the value CSR_WIFI_NME_AP_PRIM will be handled
 *      message:    the message to free
 *----------------------------------------------------------------------------*/
void CsrWifiNmeApFreeUpstreamMessageContents(u16 eventClass, void *message)
{
    if (eventClass != CSR_WIFI_NME_AP_PRIM)
    {
        return;
    }
    if (NULL == message)
    {
        return;
    }
}



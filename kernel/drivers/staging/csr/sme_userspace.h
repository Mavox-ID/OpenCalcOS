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
#ifndef __BEEP_SME_USERSPACE_H__
#define __BEEP_SME_USERSPACE_H__ 1

#include <beep/kernel.h>

int uf_sme_init(unifi_priv_t *priv);
void uf_sme_deinit(unifi_priv_t *priv);
int uf_sme_queue_message(unifi_priv_t *priv, u8 *buffer, int length);


#include "csr_wifi_router_lib.h"
#include "csr_wifi_router_sef.h"
#include "csr_wifi_router_ctrl_lib.h"
#include "csr_wifi_router_ctrl_sef.h"
#include "csr_wifi_sme_task.h"
#ifdef CSR_SUPPORT_WEXT_AP
#include "csr_wifi_nme_ap_lib.h"
#endif
#include "csr_wifi_sme_lib.h"

void CsrWifiRouterTransportInit(unifi_priv_t *priv);
void CsrWifiRouterTransportRecv(unifi_priv_t *priv, u8 *buffer, size_t bufferLength);
void CsrWifiRouterTransportDeInit(unifi_priv_t *priv);

#endif /* __BEEP_SME_USERSPACE_H__ */

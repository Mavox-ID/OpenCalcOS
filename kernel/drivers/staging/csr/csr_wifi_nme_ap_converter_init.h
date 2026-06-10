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

#ifndef CSR_WIFI_NME_AP_CONVERTER_INIT_H__
#define CSR_WIFI_NME_AP_CONVERTER_INIT_H__

#ifndef CSR_WIFI_NME_ENABLE
#error CSR_WIFI_NME_ENABLE MUST be defined inorder to use csr_wifi_nme_ap_converter_init.h
#endif
#ifndef CSR_WIFI_AP_ENABLE
#error CSR_WIFI_AP_ENABLE MUST be defined inorder to use csr_wifi_nme_ap_converter_init.h
#endif

#ifndef EXCLUDE_CSR_WIFI_NME_AP_MODULE

#include "csr_msgconv.h"

#ifdef CSR_LOG_ENABLE
#include "csr_log.h"

extern const CsrLogPrimitiveInformation* CsrWifiNmeApTechInfoGet(void);
#endif /* CSR_LOG_ENABLE */

extern void CsrWifiNmeApConverterInit(void);

#else /* EXCLUDE_CSR_WIFI_NME_AP_MODULE */

#define CsrWifiNmeApConverterInit()

#endif /* EXCLUDE_CSR_WIFI_NME_AP_MODULE */

#endif /* CSR_WIFI_NME_AP_CONVERTER_INIT_H__ */

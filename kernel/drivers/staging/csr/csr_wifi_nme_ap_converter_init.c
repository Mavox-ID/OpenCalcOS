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

#include "csr_msgconv.h"
#include "csr_macro.h"

#ifdef CSR_WIFI_NME_ENABLE
#ifdef CSR_WIFI_AP_ENABLE

#ifdef CSR_LOG_ENABLE
#include "csr_log.h"
#endif

#ifndef EXCLUDE_CSR_WIFI_NME_AP_MODULE
#include "csr_wifi_nme_ap_serialize.h"
#include "csr_wifi_nme_ap_prim.h"

static CsrMsgConvMsgEntry csrwifinmeap_conv_lut[] = {
    { CSR_WIFI_NME_AP_CONFIG_SET_REQ, CsrWifiNmeApConfigSetReqSizeof, CsrWifiNmeApConfigSetReqSer, CsrWifiNmeApConfigSetReqDes, CsrWifiNmeApConfigSetReqSerFree },
    { CSR_WIFI_NME_AP_WPS_REGISTER_REQ, CsrWifiNmeApWpsRegisterReqSizeof, CsrWifiNmeApWpsRegisterReqSer, CsrWifiNmeApWpsRegisterReqDes, CsrWifiNmeApWpsRegisterReqSerFree },
    { CSR_WIFI_NME_AP_START_REQ, CsrWifiNmeApStartReqSizeof, CsrWifiNmeApStartReqSer, CsrWifiNmeApStartReqDes, CsrWifiNmeApStartReqSerFree },
    { CSR_WIFI_NME_AP_STOP_REQ, CsrWifiNmeApStopReqSizeof, CsrWifiNmeApStopReqSer, CsrWifiNmeApStopReqDes, CsrWifiNmeApStopReqSerFree },
    { CSR_WIFI_NME_AP_WMM_PARAM_UPDATE_REQ, CsrWifiNmeApWmmParamUpdateReqSizeof, CsrWifiNmeApWmmParamUpdateReqSer, CsrWifiNmeApWmmParamUpdateReqDes, CsrWifiNmeApWmmParamUpdateReqSerFree },
    { CSR_WIFI_NME_AP_STA_REMOVE_REQ, CsrWifiNmeApStaRemoveReqSizeof, CsrWifiNmeApStaRemoveReqSer, CsrWifiNmeApStaRemoveReqDes, CsrWifiNmeApStaRemoveReqSerFree },
    { CSR_WIFI_NME_AP_CONFIG_SET_CFM, CsrWifiNmeApConfigSetCfmSizeof, CsrWifiNmeApConfigSetCfmSer, CsrWifiNmeApConfigSetCfmDes, CsrWifiNmeApConfigSetCfmSerFree },
    { CSR_WIFI_NME_AP_WPS_REGISTER_CFM, CsrWifiNmeApWpsRegisterCfmSizeof, CsrWifiNmeApWpsRegisterCfmSer, CsrWifiNmeApWpsRegisterCfmDes, CsrWifiNmeApWpsRegisterCfmSerFree },
    { CSR_WIFI_NME_AP_START_CFM, CsrWifiNmeApStartCfmSizeof, CsrWifiNmeApStartCfmSer, CsrWifiNmeApStartCfmDes, CsrWifiNmeApStartCfmSerFree },
    { CSR_WIFI_NME_AP_STOP_CFM, CsrWifiNmeApStopCfmSizeof, CsrWifiNmeApStopCfmSer, CsrWifiNmeApStopCfmDes, CsrWifiNmeApStopCfmSerFree },
    { CSR_WIFI_NME_AP_STOP_IND, CsrWifiNmeApStopIndSizeof, CsrWifiNmeApStopIndSer, CsrWifiNmeApStopIndDes, CsrWifiNmeApStopIndSerFree },
    { CSR_WIFI_NME_AP_WMM_PARAM_UPDATE_CFM, CsrWifiNmeApWmmParamUpdateCfmSizeof, CsrWifiNmeApWmmParamUpdateCfmSer, CsrWifiNmeApWmmParamUpdateCfmDes, CsrWifiNmeApWmmParamUpdateCfmSerFree },
    { CSR_WIFI_NME_AP_STATION_IND, CsrWifiNmeApStationIndSizeof, CsrWifiNmeApStationIndSer, CsrWifiNmeApStationIndDes, CsrWifiNmeApStationIndSerFree },

    { 0, NULL, NULL, NULL, NULL },
};

CsrMsgConvMsgEntry* CsrWifiNmeApConverterLookup(CsrMsgConvMsgEntry *ce, u16 msgType)
{
    if (msgType & CSR_PRIM_UPSTREAM)
    {
        u16 idx = (msgType & ~CSR_PRIM_UPSTREAM) + CSR_WIFI_NME_AP_PRIM_DOWNSTREAM_COUNT;
        if (idx < (CSR_WIFI_NME_AP_PRIM_UPSTREAM_COUNT + CSR_WIFI_NME_AP_PRIM_DOWNSTREAM_COUNT) &&
            csrwifinmeap_conv_lut[idx].msgType == msgType)
        {
            return &csrwifinmeap_conv_lut[idx];
        }
    }
    else
    {
        if (msgType < CSR_WIFI_NME_AP_PRIM_DOWNSTREAM_COUNT &&
            csrwifinmeap_conv_lut[msgType].msgType == msgType)
        {
            return &csrwifinmeap_conv_lut[msgType];
        }
    }
    return NULL;
}


void CsrWifiNmeApConverterInit(void)
{
    CsrMsgConvInsert(CSR_WIFI_NME_AP_PRIM, csrwifinmeap_conv_lut);
    CsrMsgConvCustomLookupRegister(CSR_WIFI_NME_AP_PRIM, CsrWifiNmeApConverterLookup);
}


#ifdef CSR_LOG_ENABLE
static const CsrLogPrimitiveInformation csrwifinmeap_conv_info = {
    CSR_WIFI_NME_AP_PRIM,
    (char *)"CSR_WIFI_NME_AP_PRIM",
    csrwifinmeap_conv_lut
};
const CsrLogPrimitiveInformation* CsrWifiNmeApTechInfoGet(void)
{
    return &csrwifinmeap_conv_info;
}


#endif /* CSR_LOG_ENABLE */
#endif /* EXCLUDE_CSR_WIFI_NME_AP_MODULE */
#endif /* CSR_WIFI_NME_ENABLE */
#endif /* CSR_WIFI_AP_ENABLE */

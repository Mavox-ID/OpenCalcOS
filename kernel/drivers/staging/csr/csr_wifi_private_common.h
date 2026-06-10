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
#ifndef CSR_WIFI_PRIVATE_COMMON_H__
#define CSR_WIFI_PRIVATE_COMMON_H__

/**
 * @brief maximum number of STAs allowed to be connected
 *
 * @par Description
 *   min & max Beacon Interval
 */
#define CSR_WIFI_AP_MAX_ASSOC_STA   8

/** Number of only b rates */
#define CSR_WIFI_SME_AP_MAX_ONLY_B_RATES        4


/** Number of mandatory b rates */
#define CSR_WIFI_SME_AP_MAX_MANDATORY_B_RATES   2


/** Number of mandatory bg rates */
#define CSR_WIFI_SME_AP_MAX_MANDATORY_BG_RATES  4


/** Number of bg rates */
#define CSR_WIFI_SME_AP_MAX_BG_RATES            12


/** Number of no b only g rates */
#define CSR_WIFI_SME_AP_MAX_NO_B_ONLY_G_RATES   8


/** Number of mandatory g rates */
#define CSR_WIFI_SME_AP_MAX_MANDATORY_G_RATES   7


/* Number of g mandatory rates */
#define CSR_WIFI_SME_AP_G_MANDATORY_RATES_NUM   7


/* Number of b mandatory rates */
#define CSR_WIFI_SME_AP_B_MANDATORY_RATES_NUM   2


/* Number of b/g mandatory rates */
#define CSR_WIFI_SME_AP_BG_MANDATORY_RATES_NUM   4


/* The maximum allowed length of SSID */
#define CSR_WIFI_SME_AP_SSID_MAX_LENGTH         32

/* Refer 8.4.2.27 RSN element - we support TKIP, WPA2, WAPI and PSK only, no pmkid, group cipher suite */
#define CSR_WIFI_SME_RSN_PACKED_SIZE (1 + 1 + 2 + 4 + 2 + 4 * 2 + 2 + 4 * 1 + 2 + 24)

/* Refer 7.3.2.9 (ISO/IEC 8802-11:2006) WAPI element - we support WAPI PSK only, no bkid, group cipher suite */
#define CSR_WIFI_SME_WAPI_PACKED_SIZE (1 + 1 + 2 + 2 + 4 * 1 + 2 + 4 * 1 + 4 + 2 + 24)


/* Common structure for NME and SME to maintain Interface mode*/
typedef u8 CsrWifiInterfaceMode;
#define  CSR_WIFI_MODE_NONE                             ((CsrWifiInterfaceMode) 0xFF)
#define  CSR_WIFI_MODE_STA                              ((CsrWifiInterfaceMode) 0x00)
#define  CSR_WIFI_MODE_AP                               ((CsrWifiInterfaceMode) 0x01)
#define  CSR_WIFI_MODE_P2P_DEVICE                       ((CsrWifiInterfaceMode) 0x02)
#define  CSR_WIFI_MODE_P2P_CLI                          ((CsrWifiInterfaceMode) 0x03)
#define  CSR_WIFI_MODE_P2P_GO                           ((CsrWifiInterfaceMode) 0x04)
#define  CSR_WIFI_MODE_AMP                              ((CsrWifiInterfaceMode) 0x05)
#define  CSR_WIFI_MODE_WPS_ENROLLEE                     ((CsrWifiInterfaceMode) 0x06)
#define  CSR_WIFI_MODE_IBSS                             ((CsrWifiInterfaceMode) 0x07)

#endif


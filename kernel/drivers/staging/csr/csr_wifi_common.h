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
#ifndef CSR_WIFI_COMMON_H__
#define CSR_WIFI_COMMON_H__

#include <beep/types.h>
#include "csr_result.h"

/* MAC address */
typedef struct
{
    u8 a[6];
} CsrWifiMacAddress;

/* IPv4 address */
typedef struct
{
    u8 a[4];
} CsrWifiIp4Address;

/* IPv6 address */
typedef struct
{
    u8 a[16];
} CsrWifiIp6Address;

typedef struct
{
    u8 ssid[32];
    u8 length;
} CsrWifiSsid;

/*******************************************************************************

  DESCRIPTION
    Result values used on the Wifi Interfaces

 VALUES
    CSR_RESULT_SUCCESS
                   - The request/procedure succeeded
    CSR_RESULT_FAILURE
                   - The request/procedure did not succeed because of an error
    CSR_WIFI_RESULT_NOT_FOUND
                   - The request did not succeed because some resource was not
                     found.
    CSR_WIFI_RESULT_TIMED_OUT
                   - The request/procedure did not succeed because of a time out
    CSR_WIFI_RESULT_CANCELLED
                   - The request was canceled due to another conflicting
                     request that was issued before this one was completed
    CSR_WIFI_RESULT_INVALID_PARAMETER
                   - The request/procedure did not succeed because it had an
                     invalid parameter
    CSR_WIFI_RESULT_NO_ROOM
                   - The request did not succeed due to a lack of resources,
                     e.g. out of memory problem.
    CSR_WIFI_RESULT_UNSUPPORTED
                   - The request/procedure did not succeed because the feature
                     is not supported yet
    CSR_WIFI_RESULT_UNAVAILABLE
                   - The request cannot be processed at this time
    CSR_WIFI_RESULT_WIFI_OFF
                   - The requested action is not available because Wi-Fi is
                     currently off
    CSR_WIFI_RESULT_SECURITY_ERROR
                   - The request/procedure did not succeed because of a security
                     error
    CSR_WIFI_RESULT_MIB_SET_FAILURE
                   - MIB Set Failure: either the MIB OID to be written to does
                     not exist or the MIB Value is invalid.
    CSR_WIFI_RESULT_INVALID_INTERFACE_TAG
                   - The supplied Interface Tag is not valid.
    CSR_WIFI_RESULT_P2P_NOA_CONFIG_CONFLICT
                   - The new NOA configuration conflicts with the existing NOA configuration
                     hence not accepted"
*******************************************************************************/
#define CSR_WIFI_RESULT_NOT_FOUND                 ((CsrResult) 0x0001)
#define CSR_WIFI_RESULT_TIMED_OUT                 ((CsrResult) 0x0002)
#define CSR_WIFI_RESULT_CANCELLED                 ((CsrResult) 0x0003)
#define CSR_WIFI_RESULT_INVALID_PARAMETER         ((CsrResult) 0x0004)
#define CSR_WIFI_RESULT_NO_ROOM                   ((CsrResult) 0x0005)
#define CSR_WIFI_RESULT_UNSUPPORTED               ((CsrResult) 0x0006)
#define CSR_WIFI_RESULT_UNAVAILABLE               ((CsrResult) 0x0007)
#define CSR_WIFI_RESULT_WIFI_OFF                  ((CsrResult) 0x0008)
#define CSR_WIFI_RESULT_SECURITY_ERROR            ((CsrResult) 0x0009)
#define CSR_WIFI_RESULT_MIB_SET_FAILURE           ((CsrResult) 0x000A)
#define CSR_WIFI_RESULT_INVALID_INTERFACE_TAG     ((CsrResult) 0x000B)
#define CSR_WIFI_RESULT_P2P_NOA_CONFIG_CONFLICT   ((CsrResult) 0x000C)

#define CSR_WIFI_VERSION	"5.1.0.0"

#endif


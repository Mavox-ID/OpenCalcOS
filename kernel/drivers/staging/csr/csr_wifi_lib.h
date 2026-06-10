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
#ifndef CSR_WIFI_LIB_H__
#define CSR_WIFI_LIB_H__

#include "csr_wifi_fsm_event.h"

/*----------------------------------------------------------------------------*
 *  CsrWifiFsmEventInit
 *
 *  DESCRIPTION
 *      Macro to initialise the members of a CsrWifiFsmEvent.
 *----------------------------------------------------------------------------*/
#define CsrWifiFsmEventInit(evt, p_primtype, p_msgtype, p_dst, p_src) \
    (evt)->primtype = p_primtype; \
    (evt)->type = p_msgtype; \
    (evt)->destination = p_dst; \
    (evt)->source = p_src


/*----------------------------------------------------------------------------*
 *  CsrWifiEvent_struct
 *
 *  DESCRIPTION
 *      Generic message creator.
 *      Allocates and fills in a message with the signature CsrWifiEvent
 *
 *----------------------------------------------------------------------------*/
CsrWifiFsmEvent* CsrWifiEvent_struct(u16 primtype, u16 msgtype, CsrSchedQid dst, CsrSchedQid src);

typedef struct
{
    CsrWifiFsmEvent common;
    u8        value;
} CsrWifiEventCsrUint8;

/*----------------------------------------------------------------------------*
 *  CsrWifiEventCsrUint8_struct
 *
 *  DESCRIPTION
 *      Generic message creator.
 *      Allocates and fills in a message with the signature CsrWifiEventCsrUint8
 *
 *----------------------------------------------------------------------------*/
CsrWifiEventCsrUint8* CsrWifiEventCsrUint8_struct(u16 primtype, u16 msgtype, CsrSchedQid dst, CsrSchedQid src, u8 value);

typedef struct
{
    CsrWifiFsmEvent common;
    u16       value;
} CsrWifiEventCsrUint16;

/*----------------------------------------------------------------------------*
 *  CsrWifiEventCsrUint16_struct
 *
 *  DESCRIPTION
 *      Generic message creator.
 *      Allocates and fills in a message with the signature CsrWifiEventCsrUint16
 *
 *----------------------------------------------------------------------------*/
CsrWifiEventCsrUint16* CsrWifiEventCsrUint16_struct(u16 primtype, u16 msgtype, CsrSchedQid dst, CsrSchedQid src, u16 value);

typedef struct
{
    CsrWifiFsmEvent common;
    u32       value;
} CsrWifiEventCsrUint32;

/*----------------------------------------------------------------------------*
 *  CsrWifiEventCsrUint32_struct
 *
 *  DESCRIPTION
 *      Generic message creator.
 *      Allocates and fills in a message with the signature CsrWifiEventCsrUint32
 *
 *----------------------------------------------------------------------------*/
CsrWifiEventCsrUint32* CsrWifiEventCsrUint32_struct(u16 primtype, u16 msgtype, CsrSchedQid dst, CsrSchedQid src, u32 value);

typedef struct
{
    CsrWifiFsmEvent common;
    u16       value16;
    u8        value8;
} CsrWifiEventCsrUint16CsrUint8;

/*----------------------------------------------------------------------------*
 *  CsrWifiEventCsrUint16CsrUint8_struct
 *
 *  DESCRIPTION
 *      Generic message creator.
 *      Allocates and fills in a message with the signature CsrWifiEventCsrUint16CsrUint8
 *
 *----------------------------------------------------------------------------*/
CsrWifiEventCsrUint16CsrUint8* CsrWifiEventCsrUint16CsrUint8_struct(u16 primtype, u16 msgtype, CsrSchedQid dst, CsrSchedQid src, u16 value16, u8 value8);

#endif /* CSR_WIFI_LIB_H__ */

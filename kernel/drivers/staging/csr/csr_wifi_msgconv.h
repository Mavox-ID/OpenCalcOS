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
#ifndef CSR_WIFI_MSGCONV_H__
#define CSR_WIFI_MSGCONV_H__

#include "csr_prim_defs.h"
#include "csr_sched.h"

void CsrUint16SerBigEndian(u8 *ptr, size_t *len, u16 v);
void CsrUint24SerBigEndian(u8 *ptr, size_t *len, u32 v);
void CsrUint32SerBigEndian(u8 *ptr, size_t *len, u32 v);

void CsrUint16DesBigEndian(u16 *v, u8 *buffer, size_t *offset);
void CsrUint24DesBigEndian(u32 *v, u8 *buffer, size_t *offset);
void CsrUint32DesBigEndian(u32 *v, u8 *buffer, size_t *offset);

void CsrUint24Ser(u8 *ptr, size_t *len, u32 v);
void CsrUint24Des(u32 *v, u8 *buffer, size_t *offset);


size_t CsrWifiEventSizeof(void *msg);
u8* CsrWifiEventSer(u8 *ptr, size_t *len, void *msg);
void* CsrWifiEventDes(u8 *buffer, size_t length);

size_t CsrWifiEventCsrUint8Sizeof(void *msg);
u8* CsrWifiEventCsrUint8Ser(u8 *ptr, size_t *len, void *msg);
void* CsrWifiEventCsrUint8Des(u8 *buffer, size_t length);

size_t CsrWifiEventCsrUint16Sizeof(void *msg);
u8* CsrWifiEventCsrUint16Ser(u8 *ptr, size_t *len, void *msg);
void* CsrWifiEventCsrUint16Des(u8 *buffer, size_t length);

size_t CsrWifiEventCsrUint32Sizeof(void *msg);
u8* CsrWifiEventCsrUint32Ser(u8 *ptr, size_t *len, void *msg);
void* CsrWifiEventCsrUint32Des(u8 *buffer, size_t length);

size_t CsrWifiEventCsrUint16CsrUint8Sizeof(void *msg);
u8* CsrWifiEventCsrUint16CsrUint8Ser(u8 *ptr, size_t *len, void *msg);
void* CsrWifiEventCsrUint16CsrUint8Des(u8 *buffer, size_t length);

#endif /* CSR_WIFI_MSGCONV_H__ */

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

#ifndef CSR_WIFI_ROUTER_TASK_H__
#define CSR_WIFI_ROUTER_TASK_H__

#include "csr_sched.h"

#define CSR_WIFI_ROUTER_LOG_ID 0x1201FFFF
extern CsrSchedQid CSR_WIFI_ROUTER_IFACEQUEUE;
void CsrWifiRouterInit(void **gash);
void CsrWifiRouterDeinit(void **gash);
void CsrWifiRouterHandler(void **gash);

#endif /* CSR_WIFI_ROUTER_TASK_H__ */


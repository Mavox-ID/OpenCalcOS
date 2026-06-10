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
#ifndef CSR_WIFI_FSM_EVENT_H
#define CSR_WIFI_FSM_EVENT_H

#include "csr_prim_defs.h"
#include "csr_sched.h"

/**
 * @brief
 *   FSM event header.
 *
 * @par Description
 *   All events MUST have this struct as the FIRST member.
 *   The next member is used internally for linked lists
 */
typedef struct CsrWifiFsmEvent
{
    CsrPrim     type;
    u16   primtype;
    CsrSchedQid destination;
    CsrSchedQid source;

    /* Private pointer to allow an optimal Event list */
    /* NOTE: Ignore this pointer.
     *       Do not waste code initializing OR freeing it.
     *       The pointer is used internally in the CsrWifiFsm code
     *       to avoid a second malloc when queuing events.
     */
    struct CsrWifiFsmEvent *next;
} CsrWifiFsmEvent;

#endif /* CSR_WIFI_FSM_EVENT_H */


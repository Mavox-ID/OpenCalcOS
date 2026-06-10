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
#ifndef	__MLME_OSDEP_H_
#define __MLME_OSDEP_H_

#include "osdep_service.h"
#include "drv_types.h"

void r8712_init_mlme_timer(struct _adapter *padapter);
void r8712_os_indicate_disconnect(struct _adapter *adapter);
void r8712_os_indicate_connect(struct _adapter *adapter);
void r8712_report_sec_ie(struct _adapter *adapter, u8 authmode, u8 *sec_ie);
int r8712_recv_indicatepkts_in_order(struct _adapter *adapter,
				struct recv_reorder_ctrl *precvreorder_ctrl,
				int bforced);
void r8712_indicate_wx_assoc_event(struct _adapter *padapter);
void r8712_indicate_wx_disassoc_event(struct _adapter *padapter);

#endif	/*_MLME_OSDEP_H_*/


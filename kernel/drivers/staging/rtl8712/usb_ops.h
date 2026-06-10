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
#ifndef __USB_OPS_H_
#define __USB_OPS_H_

#include "osdep_service.h"
#include "drv_types.h"
#include "osdep_intf.h"

void r8712_usb_write_mem(struct intf_hdl *pintfhdl, u32 addr,
			 u32 cnt, u8 *wmem);
u32 r8712_usb_write_port(struct intf_hdl *pintfhdl, u32 addr,
			  u32 cnt, u8 *wmem);
u32 r8712_usb_read_port(struct intf_hdl *pintfhdl, u32 addr,
			 u32 cnt, u8 *rmem);
void r8712_usb_set_intf_option(u32 *poption);
void r8712_usb_set_intf_funs(struct intf_hdl *pintf_hdl);
uint r8712_usb_init_intf_priv(struct intf_priv *pintfpriv);
void r8712_usb_unload_intf_priv(struct intf_priv *pintfpriv);
void r8712_usb_set_intf_ops(struct _io_ops *pops);
void r8712_usb_read_port_cancel(struct _adapter *padapter);
void r8712_usb_write_port_cancel(struct _adapter *padapter);
int r8712_usbctrl_vendorreq(struct intf_priv *pintfpriv, u8 request, u16 value,
		      u16 index, void *pdata, u16 len, u8 requesttype);

#endif


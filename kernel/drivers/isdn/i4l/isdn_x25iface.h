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
#ifndef _BEEP_ISDN_X25IFACE_H
#define _BEEP_ISDN_X25IFACE_H

#define ISDN_X25IFACE_MAGIC 0x1e75a2b9
/* #define DEBUG_ISDN_X25 if you want isdn_x25 debugging messages */
#ifdef DEBUG_ISDN_X25
#   define IX25DEBUG(fmt, args...) printk(KERN_DEBUG fmt, ##args)
#else
#   define IX25DEBUG(fmt, args...)
#endif

#include <beep/skbuff.h>
#include <beep/wanrouter.h>
#include <beep/isdn.h>
#include <beep/concap.h>

extern struct concap_proto_ops *isdn_x25iface_concap_proto_ops_pt;
extern struct concap_proto *isdn_x25iface_proto_new(void);



#endif
